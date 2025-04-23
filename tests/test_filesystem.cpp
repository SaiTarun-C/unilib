#include <gtest/gtest.h>
#include "filesystem_utils.hpp"

TEST(FilesystemTest, CreateFile) {
    FilesystemUtils fs;
    bool created = fs.createFile("test_file.txt");
    EXPECT_TRUE(created);
}

TEST(FilesystemTest, ReadFile) {
    FilesystemUtils fs;
    fs.createFile("test_file.txt");
    std::string content = fs.readFile("test_file.txt");
    EXPECT_EQ(content, "Test content");
}
