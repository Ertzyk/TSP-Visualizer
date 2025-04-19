#include "ConfigLoader.h"
#include <fstream>
#include "external/nlohmann/json.hpp"
#include <stdexcept>

using json = nlohmann::json;

std::string ConfigLoader::load_api_key(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open config file: " + filename);
    }
    json j;
    file >> j;
    if (!j.contains("ors_api_key")) {
        throw std::runtime_error("Missing 'ors_api_key' in config file");
    }
    return j["ors_api_key"].get<std::string>();
}