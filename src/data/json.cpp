#include "data/json.hpp"
#include <fstream>
#include <sstream>

namespace unilib::data {

bool JsonWrapper::parseFromString(const std::string& jsonStr) {
    try {
        jsonData_ = nlohmann::json::parse(jsonStr);
        return true;
    } catch (const std::exception& e) {
        lastError_ = e.what();
        return false;
    }
}

bool JsonWrapper::parseFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        lastError_ = "Unable to open file: " + filename;
        return false;
    }

    try {
        file >> jsonData_;
        return true;
    } catch (const std::exception& e) {
        lastError_ = e.what();
        return false;
    }
}

std::string JsonWrapper::stringify(bool pretty) const {
    try {
        return pretty ? jsonData_.dump(4) : jsonData_.dump();
    } catch (...) {
        return "{}";
    }
}

bool JsonWrapper::saveToFile(const std::string& filename, bool pretty) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    try {
        file << stringify(pretty);
        return true;
    } catch (...) {
        return false;
    }
}

nlohmann::json& JsonWrapper::data() {
    return jsonData_;
}

const std::string& JsonWrapper::lastError() const {
    return lastError_;
}

} // namespace unilib::data
