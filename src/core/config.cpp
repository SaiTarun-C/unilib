#include "core/config.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <json/json.h> // Assume using a JSON library like jsoncpp

namespace unilib::core {

Config::Config(const std::string& config_file) : config_file_(config_file) {
    if (!config_file_.empty()) {
        LoadConfigFile(config_file_);
    }
}

void Config::LoadConfigFile(const std::string& config_file) {
    std::ifstream file(config_file);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open config file: " + config_file);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    Json::Reader reader;
    Json::Value root;
    if (!reader.parse(buffer.str(), root)) {
        throw std::runtime_error("Failed to parse config file: " + config_file);
    }

    // Example of reading configuration settings
    if (root.isMember("log_level")) {
        log_level_ = root["log_level"].asString();
    } else {
        log_level_ = "INFO"; // Default
    }

    if (root.isMember("output_file")) {
        log_file_ = root["output_file"].asString();
    }
}

std::string Config::GetConfigValue(const std::string& key) const {
    if (key == "log_level") {
        return log_level_;
    }
    if (key == "output_file") {
        return log_file_;
    }
    throw std::invalid_argument("Config key not found: " + key);
}

} // namespace unilib::core
