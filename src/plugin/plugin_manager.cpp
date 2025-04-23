#include "plugin/plugin_manager.hpp"
#include <stdexcept>
#include <iostream>

#if defined(_WIN32)
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

namespace unilib::plugin {

PluginManager::~PluginManager() {
    unload_all();
}

bool PluginManager::load_plugin(const std::string& path) {
    if (loaded_plugins_.count(path)) {
        std::cerr << "[PluginManager] Plugin already loaded: " << path << std::endl;
        return false;
    }

#if defined(_WIN32)
    HMODULE handle = LoadLibraryA(path.c_str());
    if (!handle) {
        std::cerr << "[PluginManager] Failed to load plugin (Windows): " << path << std::endl;
        return false;
    }
#else
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "[PluginManager] Failed to load plugin (Unix): " << dlerror() << std::endl;
        return false;
    }
#endif

    loaded_plugins_[path] = handle;
    std::cout << "[PluginManager] Plugin loaded successfully: " << path << std::endl;
    return true;
}

void* PluginManager::get_symbol(const std::string& path, const std::string& symbol_name) {
    if (!loaded_plugins_.count(path)) {
        std::cerr << "[PluginManager] Plugin not loaded: " << path << std::endl;
        return nullptr;
    }

#if defined(_WIN32)
    void* symbol = GetProcAddress(static_cast<HMODULE>(loaded_plugins_[path]), symbol_name.c_str());
#else
    void* symbol = dlsym(loaded_plugins_[path], symbol_name.c_str());
#endif

    if (!symbol) {
        std::cerr << "[PluginManager] Failed to get symbol: " << symbol_name << std::endl;
    }

    return symbol;
}

bool PluginManager::unload_plugin(const std::string& path) {
    auto it = loaded_plugins_.find(path);
    if (it == loaded_plugins_.end()) {
        std::cerr << "[PluginManager] Plugin not found: " << path << std::endl;
        return false;
    }

#if defined(_WIN32)
    if (!FreeLibrary(static_cast<HMODULE>(it->second))) {
        std::cerr << "[PluginManager] Failed to unload plugin (Windows): " << path << std::endl;
        return false;
    }
#else
    if (dlclose(it->second) != 0) {
        std::cerr << "[PluginManager] Failed to unload plugin (Unix): " << dlerror() << std::endl;
        return false;
    }
#endif

    std::cout << "[PluginManager] Plugin unloaded successfully: " << path << std::endl;
    loaded_plugins_.erase(it);
    return true;
}

void PluginManager::unload_all() {
    for (const auto& [path, handle] : loaded_plugins_) {
#if defined(_WIN32)
        FreeLibrary(static_cast<HMODULE>(handle));
#else
        dlclose(handle);
#endif
        std::cout << "[PluginManager] Plugin unloaded: " << path << std::endl;
    }
    loaded_plugins_.clear();
}

} // namespace unilib::plugin
