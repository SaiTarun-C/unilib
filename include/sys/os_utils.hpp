#ifndef UNILIB_SYS_OS_UTILS_HPP
#define UNILIB_SYS_OS_UTILS_HPP

#include <string>
#include <cstdlib>
#include <stdexcept>

#if defined(_WIN32)
    #define UNILIB_OS_WINDOWS
#elif defined(__linux__)
    #define UNILIB_OS_LINUX
#elif defined(__APPLE__)
    #define UNILIB_OS_MAC
#else
    #define UNILIB_OS_UNKNOWN
#endif

namespace unilib::sys {

// Returns the name of the current OS
inline std::string os_name() {
#if defined(UNILIB_OS_WINDOWS)
    return "Windows";
#elif defined(UNILIB_OS_LINUX)
    return "Linux";
#elif defined(UNILIB_OS_MAC)
    return "macOS";
#else
    return "Unknown";
#endif
}

// Returns the value of an environment variable
inline std::string get_env(const std::string& var) {
    const char* val = std::getenv(var.c_str());
    if (!val) return "";
    return std::string(val);
}

// Returns the number of logical CPU cores
inline unsigned int cpu_cores() {
    return std::thread::hardware_concurrency();
}

} // namespace unilib::sys

#endif // UNILIB_SYS_OS_UTILS_HPP
