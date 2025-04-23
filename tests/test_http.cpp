#include <gtest/gtest.h>
#include "http.hpp"

TEST(HTTPTest, GetRequest) {
    HTTPClient client;
    std::string response = client.get("http://httpbin.org/get");

    EXPECT_NE(response.find("HTTP/1.1 200 OK"), std::string::npos);
}

TEST(HTTPTest, PostRequest) {
    HTTPClient client;
    std::string response = client.post("http://httpbin.org/post", "{\"key\":\"value\"}");

    EXPECT_NE(response.find("HTTP/1.1 200 OK"), std::string::npos);
}
