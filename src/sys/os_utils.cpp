#include "sys/os_utils.hpp"

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
    #include <limits.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
    #include <unistd.h>
#endif

#include <cstdlib>
#include <iostream>

namespace unilib::sys {

std::string getOSName() {
#if defined(_WIN32)
    return "Windows";
#elif defined(__linux__)
    return "Linux";
#elif defined(__APPLE__)
    return "macOS";
#else
    return "Unknown";
#endif
}

std::string getEnvVar(const std::string& name) {
    const char* val = std::getenv(name.c_str());
    return val ? std::string(val) : "";
}

std::string getExecutablePath() {
    char buffer[4096];

#if defined(_WIN32)
    DWORD len = GetModuleFileNameA(nullptr, buffer, sizeof(buffer));
    return std::string(buffer, len);
#elif defined(__linux__)
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        return std::string(buffer);
    }
#elif defined(__APPLE__)
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) == 0) {
        return std::string(buffer);
    }
#endif

    return {};
}

unsigned int getCPUCoreCount() {
#if defined(_WIN32)
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#else
    return static_cast<unsigned int>(sysconf(_SC_NPROCESSORS_ONLN));
#endif
}

} // namespace unilib::sys
