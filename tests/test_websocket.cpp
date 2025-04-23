#include <gtest/gtest.h>
#include "websocket.hpp"

TEST(WebSocketTest, Connect) {
    WebSocket ws("ws://echo.websocket.org");
    bool connected = ws.connect();
    EXPECT_TRUE(connected);
}

TEST(WebSocketTest, SendMessage) {
    WebSocket ws("ws://echo.websocket.org");
    ws.connect();
    std::string message = "Hello WebSocket";
    std::string response = ws.sendMessage(message);
    EXPECT_EQ(response, message);  // Echo server should return the same message
}
