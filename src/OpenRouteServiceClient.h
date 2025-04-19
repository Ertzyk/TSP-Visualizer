#ifndef OPENROUTESERVICECLIENT_H
#define OPENROUTESERVICECLIENT_H

#include <string>
#include <vector>
#include <utility>

class OpenRouteServiceClient {
private:
    std::string apiKey;
public:
    explicit OpenRouteServiceClient(const std::string& key);
    std::vector<std::pair<double, double>> get_coordinates(const std::vector<std::string>& cityNames);
    std::vector<std::vector<double>> get_duration_matrix(const std::vector<std::pair<double, double>>& coords);
};

#endif