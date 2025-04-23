//Purpose: Demonstrates HTTP GET request and WebSocket echo.

#include "http_client.hpp"
#include "websocket_client.hpp"

int main() {
    HTTPClient http;
    auto response = http.get("https://httpbin.org/get");
    if (response.success) {
        std::cout << "HTTP GET Response:\n" << response.body << std::endl;
    } else {
        std::cerr << "HTTP GET failed: " << response.error << std::endl;
    }

    WebSocketClient ws("wss://echo.websocket.org");
    if (ws.connect()) {
        ws.send("Hello, WebSocket!");
        auto message = ws.receive();
        std::cout << "WebSocket Echo: " << message << std::endl;
        ws.close();
    } else {
        std::cerr << "WebSocket connection failed." << std::endl;
    }

    return 0;
}
