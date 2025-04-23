//Purpose: Demonstrates dynamic plugin loading (cross-platform safe).

#include "plugin_manager.hpp"
#include <iostream>

int main() {
    PluginManager manager;

#ifdef _WIN32
    std::string pluginPath = "example_plugin.dll";
#else
    std::string pluginPath = "./libexample_plugin.so";
#endif

    if (!manager.loadPlugin(pluginPath)) {
        std::cerr << "Failed to load plugin: " << pluginPath << std::endl;
        return 1;
    }

    auto pluginFunc = manager.getFunction<void(*)()>("plugin_entry");
    if (pluginFunc) {
        std::cout << "Calling plugin function...\n";
        pluginFunc();
    } else {
        std::cerr << "Function not found in plugin.\n";
    }

    manager.unloadPlugin();
    return 0;
}
