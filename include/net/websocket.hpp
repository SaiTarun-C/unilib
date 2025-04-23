// File: include/net/websocket.hpp

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#ifndef UNILIB_NET_WEBSOCKET_HPP
#define UNILIB_NET_WEBSOCKET_HPP

#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <atomic>
#include <stdexcept>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

namespace unilib::net {

using WebsocketClientBase = websocketpp::client<websocketpp::config::asio_client>;

class WebsocketClient {
public:
    WebsocketClient() : running_(false) {
        client_.init_asio();

        client_.set_message_handler([this](websocketpp::connection_hdl, WebsocketClientBase::message_ptr msg) {
            std::lock_guard<std::mutex> lock(msg_mutex_);
            messages_.push(msg->get_payload());
        });
    }

    void connect(const std::string& uri) {
        websocketpp::lib::error_code ec;
        auto con = client_.get_connection(uri, ec);
        if (ec) throw std::runtime_error("Connection error: " + ec.message());

        hdl_ = con->get_handle();
        client_.connect(con);

        running_ = true;
        ws_thread_ = std::thread([this]() { client_.run(); });
    }

    void send(const std::string& msg) {
        if (!running_) throw std::runtime_error("WebSocket not connected");
        client_.send(hdl_, msg, websocketpp::frame::opcode::text);
    }

    std::string receive() {
        std::lock_guard<std::mutex> lock(msg_mutex_);
        if (messages_.empty()) return "";
        std::string msg = messages_.front();
        messages_.pop();
        return msg;
    }

    void close() {
        if (running_) {
            client_.close(hdl_, websocketpp::close::status::going_away, "Shutdown");
            if (ws_thread_.joinable()) ws_thread_.join();
            running_ = false;
        }
    }

    ~WebsocketClient() {
        close();
    }

private:
    WebsocketClientBase client_;
    websocketpp::connection_hdl hdl_;
    std::thread ws_thread_;
    std::atomic<bool> running_;
    std::queue<std::string> messages_;
    std::mutex msg_mutex_;
};

} // namespace unilib::net

#endif // UNILIB_NET_WEBSOCKET_HPP
