#include <gtest/gtest.h>
#include "config.hpp"

TEST(ConfigTest, LoadConfig) {
    Config config;

    // Load a sample configuration
    EXPECT_TRUE(config.load("test_config.json"));

    // Check if a specific configuration setting is loaded
    std::string expected_value = "value_from_config";
    EXPECT_EQ(config.get<std::string>("key"), expected_value);
}

TEST(ConfigTest, MissingConfig) {
    Config config;

    // Try loading a non-existent configuration file
    EXPECT_FALSE(config.load("non_existent_config.json"));
}
