#include <gtest/gtest.h>
#include "plugin_manager.hpp"

TEST(PluginTest, LoadPlugin) {
    PluginManager pm;
    bool loaded = pm.loadPlugin("test_plugin.so");
    EXPECT_TRUE(loaded);
}

TEST(PluginTest, ExecutePlugin) {
    PluginManager pm;
    pm.loadPlugin("test_plugin.so");

    std::string result = pm.executePlugin("TestPluginFunction");
    EXPECT_EQ(result, "Plugin function executed");
}
