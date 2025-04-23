#pragma once
#include <string>
#include <unordered_map>

namespace unilib::plugin {

class PluginManager {
public:
    ~PluginManager();

    bool load_plugin(const std::string& path);
    void* get_symbol(const std::string& path, const std::string& symbol_name);
    bool unload_plugin(const std::string& path);
    void unload_all();

private:
    std::unordered_map<std::string, void*> loaded_plugins_;
};

} // namespace unilib::plugin
