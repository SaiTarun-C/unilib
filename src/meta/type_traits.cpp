#include "meta/type_traits.hpp"
#include <typeinfo>
#include <cxxabi.h>
#include <cstdlib>
#include <mutex>

namespace unilib::meta {

namespace {

// Utility to demangle C++ type names
std::string demangle_type_name(const char* name) {
    int status = -1;
    char* demangled = abi::__cxa_demangle(name, nullptr, nullptr, &status);
    std::string result = (status == 0 && demangled) ? demangled : name;
    std::free(demangled);
    return result;
}

} // anonymous namespace

std::string type_name_cache(const std::type_info& typeInfo) {
    static std::mutex mtx;
    static std::unordered_map<std::size_t, std::string> cache;

    std::lock_guard<std::mutex> lock(mtx);
    auto hash = typeInfo.hash_code();
    auto it = cache.find(hash);
    if (it != cache.end())
        return it->second;

    std::string name = demangle_type_name(typeInfo.name());
    cache[hash] = name;
    return name;
}

bool is_power_of_two(std::size_t value) {
    return value != 0 && (value & (value - 1)) == 0;
}

} // namespace unilib::meta
