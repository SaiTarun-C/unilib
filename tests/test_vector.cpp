#include <gtest/gtest.h>
#include "vector.hpp"

TEST(VectorTest, PushBack) {
    CustomVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}

TEST(VectorTest, Resize) {
    CustomVector<int> vec;
    vec.push_back(1);
    vec.resize(5);

    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[4], 0);  // Default value after resizing
}
