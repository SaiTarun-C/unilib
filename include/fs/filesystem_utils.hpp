#ifndef UNILIB_FS_FILESYSTEM_UTILS_HPP
#define UNILIB_FS_FILESYSTEM_UTILS_HPP

#include <filesystem>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>

namespace unilib::fs {

namespace fs = std::filesystem;

// Check if a path exists
inline bool exists(const std::string& path) {
    return fs::exists(path);
}

// Check if a path is a directory
inline bool is_directory(const std::string& path) {
    return fs::is_directory(path);
}

// Check if a path is a regular file
inline bool is_file(const std::string& path) {
    return fs::is_regular_file(path);
}

// Create a single directory
inline bool create_directory(const std::string& path) {
    return fs::create_directory(path);
}

// Create directories recursively
inline bool create_directories(const std::string& path) {
    return fs::create_directories(path);
}

// Remove a file or directory (recursive)
inline bool remove_path(const std::string& path) {
    return fs::remove_all(path) > 0;
}

// Rename or move a file
inline void rename(const std::string& from, const std::string& to) {
    fs::rename(from, to);
}

// Copy file or directory
inline void copy_path(const std::string& from, const std::string& to, bool recursive = true, bool overwrite = false) {
    fs::copy_options options = fs::copy_options::none;

    if (recursive) options |= fs::copy_options::recursive;
    if (overwrite) options |= fs::copy_options::overwrite_existing;

    fs::copy(from, to, options);
}

// Get absolute path
inline std::string absolute_path(const std::string& path) {
    return fs::absolute(path).string();
}

// Get the size of a file
inline std::uintmax_t file_size(const std::string& path) {
    if (!fs::exists(path) || !fs::is_regular_file(path))
        throw std::runtime_error("Invalid file for size: " + path);
    return fs::file_size(path);
}

// Read an entire file as string (text mode)
inline std::string read_file(const std::string& path) {
    std::ifstream file(path);
    if (!file)
        throw std::runtime_error("Failed to open file: " + path);

    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

// Write string to file (overwrite)
inline void write_file(const std::string& path, const std::string& content) {
    std::ofstream file(path, std::ios::trunc);
    if (!file)
        throw std::runtime_error("Failed to write to file: " + path);
    file << content;
}

// List files and folders (non-recursive)
inline std::vector<std::string> list_directory(const std::string& dir_path) {
    std::vector<std::string> entries;
    if (!fs::exists(dir_path) || !fs::is_directory(dir_path))
        throw std::runtime_error("Invalid directory: " + dir_path);

    for (const auto& entry : fs::directory_iterator(dir_path)) {
        entries.push_back(entry.path().string());
    }
    return entries;
}

// List files only (recursive optional)
inline std::vector<std::string> list_files(const std::string& dir_path, bool recursive = false) {
    std::vector<std::string> files;
    if (!fs::exists(dir_path) || !fs::is_directory(dir_path))
        throw std::runtime_error("Invalid directory: " + dir_path);

    if (recursive) {
        for (const auto& entry : fs::recursive_directory_iterator(dir_path)) {
            if (fs::is_regular_file(entry)) {
                files.emplace_back(entry.path().string());
            }
        }
    } else {
        for (const auto& entry : fs::directory_iterator(dir_path)) {
            if (fs::is_regular_file(entry)) {
                files.emplace_back(entry.path().string());
            }
        }
    }
    return files;
}

// Get current working directory
inline std::string current_path() {
    return fs::current_path().string();
}

// Set current working directory
inline void set_current_path(const std::string& path) {
    if (!fs::exists(path) || !fs::is_directory(path))
        throw std::runtime_error("Invalid path to set as current directory: " + path);
    fs::current_path(path);
}

} // namespace unilib::fs

#endif // UNILIB_FS_FILESYSTEM_UTILS_HPP
