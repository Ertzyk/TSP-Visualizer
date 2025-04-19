#include "OpenRouteServiceClient.h"
#include <curl/curl.h>
#include "external/nlohmann/json.hpp"
#include <sstream>
#include <iostream>
#include <stdexcept>

using json = nlohmann::json;

OpenRouteServiceClient::OpenRouteServiceClient(const std::string& key) : apiKey(key) {}

namespace {
    size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
        size_t totalSize = size * nmemb;
        output->append((char*)contents, totalSize);
        return totalSize;
    }
}

std::vector<std::pair<double, double>> OpenRouteServiceClient::get_coordinates(const std::vector<std::string>& cityNames) {
    std::vector<std::pair<double, double>> coordinates;
    for (const auto& city : cityNames) {
        CURL* curl = curl_easy_init();
        if (!curl) throw std::runtime_error("Failed to initialize CURL");
        std::ostringstream url;
        url << "https://api.openrouteservice.org/geocode/search?api_key=" << apiKey
            << "&text=" << curl_easy_escape(curl, city.c_str(), city.length());
        std::string response;
        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_CAINFO, "C:/libs/curl/cacert.pem");

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            curl_easy_cleanup(curl);
            throw std::runtime_error("CURL request failed: " + std::string(curl_easy_strerror(res)));
        }
        curl_easy_cleanup(curl);
        try {
            json j = json::parse(response);
            if (j.contains("features") && !j["features"].empty()) {
                auto coord = j["features"][0]["geometry"]["coordinates"];
                double lon = coord[0];
                double lat = coord[1];
                coordinates.emplace_back(lat, lon);
            } else {
                throw std::runtime_error("City not found: " + city);
            }
        } catch (const std::exception& e) {
            throw std::runtime_error("Failed to parse geocode response for city '" + city + "': " + e.what());
        }
    }

    return coordinates;
}

std::vector<std::vector<double>> OpenRouteServiceClient::get_duration_matrix(const std::vector<std::pair<double, double>>& coords) {
    CURL* curl = curl_easy_init();
    if (!curl) throw std::runtime_error("Failed to initialize CURL");
    json payload;
    for (const auto& [lat, lon] : coords) {
        payload["locations"].push_back({ lon, lat });
    }
    payload["metrics"] = { "duration" };
    payload["units"] = "m";
    std::string payloadStr = payload.dump();
    std::string response;
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, ("Authorization: " + apiKey).c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.openrouteservice.org/v2/matrix/driving-car");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadStr.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_CAINFO, "C:/libs/curl/cacert.pem");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    if (res != CURLE_OK) {
        throw std::runtime_error("Matrix API request failed: " + std::string(curl_easy_strerror(res)));
    }
    try {
        json j = json::parse(response);
        const auto& durations = j["durations"];
        std::vector<std::vector<double>> matrix;
        for (const auto& row : durations) {
            std::vector<double> mrow;
            for (const auto& val : row) {
                mrow.push_back(val);
            }
            matrix.push_back(mrow);
        }
        return matrix;
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to parse matrix response: " + std::string(e.what()));
    }
}