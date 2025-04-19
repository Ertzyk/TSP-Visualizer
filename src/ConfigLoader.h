#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <string>

class ConfigLoader {
public:
    static std::string load_api_key(const std::string& filename);
};

#endif