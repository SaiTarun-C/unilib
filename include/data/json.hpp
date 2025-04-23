#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <mutex>

namespace unilib::data {
    class JsonHandler {
    public:
        static nlohmann::json loadFromFile(const std::string& filename);
        static void saveToFile(const std::string& filename, const nlohmann::json& j);

    private:
        static std::mutex file_mutex;
    };
}