#include "fs/filesystem_utils.hpp"

#ifdef UNILIB_USE_STD_FILESYSTEM
    #include <filesystem>
    namespace fs = std::filesystem;
#else
    #include <boost/filesystem.hpp>
    namespace fs = boost::filesystem;
#endif

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace unilib::fs {

bool exists(const std::string& path) {
    return fs::exists(path);
}

bool isDirectory(const std::string& path) {
    return fs::is_directory(path);
}

bool isFile(const std::string& path) {
    return fs::is_regular_file(path);
}

bool createDirectory(const std::string& path) {
    try {
        return fs::create_directories(path);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error creating directory: " << e.what() << std::endl;
        return false;
    }
}

bool remove(const std::string& path) {
    try {
        return fs::remove_all(path) > 0;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error removing path: " << e.what() << std::endl;
        return false;
    }
}

std::uintmax_t fileSize(const std::string& path) {
    try {
        return fs::file_size(path);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error getting file size: " << e.what() << std::endl;
        return 0;
    }
}

std::vector<std::string> listDirectory(const std::string& path) {
    std::vector<std::string> result;
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            result.push_back(entry.path().string());
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error listing directory: " << e.what() << std::endl;
    }
    return result;
}

bool copyFile(const std::string& from, const std::string& to, bool overwrite) {
    try {
        if (overwrite && fs::exists(to)) {
            fs::remove(to);
        }
        fs::copy_file(from, to, fs::copy_options::overwrite_existing);
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error copying file: " << e.what() << std::endl;
        return false;
    }
}

std::string currentPath() {
    try {
        return fs::current_path().string();
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error getting current path: " << e.what() << std::endl;
        return {};
    }
}

bool writeToFile(const std::string& path, const std::string& content) {
    try {
        std::ofstream ofs(path, std::ios::out | std::ios::trunc);
        if (!ofs) return false;
        ofs << content;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error writing to file: " << e.what() << std::endl;
        return false;
    }
}

std::string readFromFile(const std::string& path) {
    try {
        std::ifstream ifs(path);
        if (!ifs) return {};
        return std::string((std::istreambuf_iterator<char>(ifs)),
                           std::istreambuf_iterator<char>());
    } catch (const std::exception& e) {
        std::cerr << "Error reading file: " << e.what() << std::endl;
        return {};
    }
}

}  // namespace unilib::fs
