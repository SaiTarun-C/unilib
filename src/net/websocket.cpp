#include "net/websocket.hpp"
#include <ixwebsocket/IXWebSocket.h>
#include <iostream>
#include <mutex>
#include <condition_variable>

namespace unilib::net {

class WebSocketClientImpl {
public:
    ix::WebSocket socket;
    std::mutex connection_mutex;
    std::condition_variable cv;
    bool connected = false;

    WebSocketClientImpl(const std::string& url) {
        socket.setUrl(url);

        socket.setOnMessageCallback([this](const ix::WebSocketMessagePtr& msg) {
            if (msg->type == ix::WebSocketMessageType::Message) {
                std::lock_guard<std::mutex> lock(callback_mutex_);
                if (message_callback_) message_callback_(msg->str);
            } else if (msg->type == ix::WebSocketMessageType::Open) {
                std::cout << "[WebSocket] Connected\n";
                {
                    std::lock_guard<std::mutex> lock(connection_mutex);
                    connected = true;
                }
                cv.notify_one();
            } else if (msg->type == ix::WebSocketMessageType::Close) {
                std::cout << "[WebSocket] Disconnected\n";
            } else if (msg->type == ix::WebSocketMessageType::Error) {
                std::cerr << "[WebSocket Error] " << msg->errorInfo.reason << std::endl;
            }
        });
    }

    void set_message_callback(std::function<void(const std::string&)> callback) {
        std::lock_guard<std::mutex> lock(callback_mutex_);
        message_callback_ = std::move(callback);
    }

    void connect() {
        socket.start();

        std::unique_lock<std::mutex> lock(connection_mutex);
        cv.wait(lock, [this] { return connected; });
    }

    void send(const std::string& msg) {
        socket.send(msg);
    }

    void stop() {
        socket.stop();
    }

private:
    std::function<void(const std::string&)> message_callback_;
    std::mutex callback_mutex_;
};

WebSocketClient::WebSocketClient(const std::string& url)
    : impl_(std::make_unique<WebSocketClientImpl>(url)) {}

WebSocketClient::~WebSocketClient() = default;

void WebSocketClient::connect() {
    impl_->connect();
}

void WebSocketClient::send(const std::string& msg) {
    impl_->send(msg);
}

void WebSocketClient::set_message_callback(std::function<void(const std::string&)> callback) {
    impl_->set_message_callback(std::move(callback));
}

void WebSocketClient::stop() {
    impl_->stop();
}

}  // namespace unilib::net
