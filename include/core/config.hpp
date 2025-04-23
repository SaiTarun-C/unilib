#pragma once

#include <string>
#include <json/json.h> // Assume using jsoncpp or similar JSON library

namespace unilib::core {

class Config {
public:
    explicit Config(const std::string& config_file = "");

    // Load the configuration file
    void LoadConfigFile(const std::string& config_file);

    // Get configuration value by key
    std::string GetConfigValue(const std::string& key) const;

private:
    std::string config_file_;
    std::string log_level_;
    std::string log_file_;
};

} // namespace unilib::core
