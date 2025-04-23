#ifndef UNILIB_BOOST_FILESYSTEM_HPP
#define UNILIB_BOOST_FILESYSTEM_HPP

#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <stdexcept>

namespace unilib::boost_ext::fs {

namespace bfs = boost::filesystem;

// Check if path exists
inline bool exists(const std::string& path) {
    return bfs::exists(bfs::path(path));
}

// Create directory (including parents)
inline bool create_directories(const std::string& path) {
    return bfs::create_directories(bfs::path(path));
}

// Remove a file or directory (recursively)
inline bool remove_path(const std::string& path) {
    return bfs::remove_all(bfs::path(path)) > 0;
}

// Get file size (throws if file doesn't exist or is a directory)
inline std::uintmax_t file_size(const std::string& path) {
    if (!bfs::exists(path) || bfs::is_directory(path))
        throw std::runtime_error("Invalid file path for size: " + path);
    return bfs::file_size(path);
}

// List directory contents (non-recursive)
inline std::vector<std::string> list_directory(const std::string& dir_path) {
    std::vector<std::string> entries;
    if (!bfs::exists(dir_path) || !bfs::is_directory(dir_path))
        throw std::runtime_error("Invalid directory: " + dir_path);

    for (const auto& entry : bfs::directory_iterator(dir_path)) {
        entries.emplace_back(entry.path().string());
    }
    return entries;
}

// Copy file
inline void copy_file(const std::string& src, const std::string& dest, bool overwrite = false) {
    bfs::copy_file(src, dest,
                   overwrite ? bfs::copy_option::overwrite_if_exists
                             : bfs::copy_option::fail_if_exists);
}

// Get absolute path
inline std::string absolute_path(const std::string& path) {
    return bfs::absolute(path).string();
}

} // namespace unilib::boost_ext::fs

#endif // UNILIB_BOOST_FILESYSTEM_HPP
