#pragma once

#include <tinyxml2.h>
#include <string>
#include <mutex>

namespace unilib::data {
    class XmlHandler {
    public:
        static tinyxml2::XMLDocument loadFromFile(const std::string& filename);
        static void saveToFile(const std::string& filename, const tinyxml2::XMLDocument& doc);

    private:
        static std::mutex file_mutex;
    };
}