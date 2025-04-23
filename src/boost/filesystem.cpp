#include "boost/filesystem.hpp"
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>

namespace unilib::boost_utils {

namespace fs = boost::filesystem;

bool FileExists(const std::string& path) {
    try {
        return fs::exists(path) && fs::is_regular_file(path);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error in FileExists: " << e.what() << std::endl;
        return false;
    }
}

bool DirectoryExists(const std::string& path) {
    try {
        return fs::exists(path) && fs::is_directory(path);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error in DirectoryExists: " << e.what() << std::endl;
        return false;
    }
}

bool CreateDirectory(const std::string& path) {
    try {
        if (!fs::exists(path)) {
            return fs::create_directories(path);
        }
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error creating directory: " << e.what() << std::endl;
        return false;
    }
}

bool RemoveFile(const std::string& path) {
    try {
        if (fs::exists(path)) {
            return fs::remove(path);
        }
        return false;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error removing file: " << e.what() << std::endl;
        return false;
    }
}

std::vector<std::string> ListFiles(const std::string& dir) {
    std::vector<std::string> files;
    try {
        if (!fs::exists(dir) || !fs::is_directory(dir)) {
            return files;
        }

        for (const auto& entry : fs::directory_iterator(dir)) {
            if (fs::is_regular_file(entry.path())) {
                files.push_back(entry.path().string());
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error listing files: " << e.what() << std::endl;
    }
    return files;
}

} // namespace unilib::boost_utils
