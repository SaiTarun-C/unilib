#include <gtest/gtest.h>
#include "string.hpp"

TEST(StringTest, Concatenate) {
    std::string result = CustomString::concatenate("Hello", " ", "World");
    EXPECT_EQ(result, "Hello World");
}

TEST(StringTest, Trim) {
    std::string str = "   hello   ";
    CustomString::trim(str);
    EXPECT_EQ(str, "hello");
}

TEST(StringTest, ToUpper) {
    std::string str = "hello";
    CustomString::toUpper(str);
    EXPECT_EQ(str, "HELLO");
}
