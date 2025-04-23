#ifndef UNILIB_BOOST_ASIO_HPP
#define UNILIB_BOOST_ASIO_HPP

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <string>
#include <iostream>
#include <functional>
#include <thread>

namespace unilib::boost_ext::net {

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

// Simple TCP client with sync/async send/receive
class TcpClient {
public:
    TcpClient(const std::string& host, uint16_t port)
        : io_context_(), socket_(io_context_) {
        tcp::resolver resolver(io_context_);
        auto endpoints = resolver.resolve(host, std::to_string(port));
        boost::asio::connect(socket_, endpoints);
    }

    ~TcpClient() {
        if (socket_.is_open())
            socket_.close();
    }

    void send(const std::string& message) {
        boost::asio::write(socket_, asio::buffer(message));
    }

    std::string receive(std::size_t size = 1024) {
        std::vector<char> buffer(size);
        boost::system::error_code ec;
        size_t len = socket_.read_some(asio::buffer(buffer), ec);
        if (ec && ec != boost::asio::error::eof)
            throw boost::system::system_error(ec);
        return std::string(buffer.data(), len);
    }

private:
    asio::io_context io_context_;
    tcp::socket socket_;
};

// Async server (simplified for brevity)
class TcpServer {
public:
    TcpServer(uint16_t port)
        : acceptor_(io_context_, tcp::endpoint(tcp::v4(), port)) {}

    void start(std::function<void(tcp::socket)> on_accept) {
        do_accept(std::move(on_accept));
        thread_ = std::thread([this]() { io_context_.run(); });
    }

    void stop() {
        io_context_.stop();
        if (thread_.joinable()) thread_.join();
    }

private:
    void do_accept(std::function<void(tcp::socket)> on_accept) {
        acceptor_.async_accept([=](boost::system::error_code ec, tcp::socket socket) {
            if (!ec)
                on_accept(std::move(socket));
            do_accept(on_accept); // Accept next connection
        });
    }

    asio::io_context io_context_;
    tcp::acceptor acceptor_;
    std::thread thread_;
};

} // namespace unilib::boost_ext::net

#endif // UNILIB_BOOST_ASIO_HPP
