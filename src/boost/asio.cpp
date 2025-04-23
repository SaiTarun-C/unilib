#include "boost/asio.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <thread>

namespace unilib::boost_utils {

using boost::asio::ip::tcp;

class TcpServer {
public:
    TcpServer(boost::asio::io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        Accept();
    }

private:
    void Accept() {
        auto socket = std::make_shared<tcp::socket>(acceptor_.get_executor().context());

        acceptor_.async_accept(*socket, [this, socket](const boost::system::error_code& ec) {
            if (!ec) {
                std::cout << "Accepted connection from " << socket->remote_endpoint() << "\n";
                std::thread([socket]() {
                    try {
                        char data[1024];
                        boost::system::error_code error;
                        size_t len = socket->read_some(boost::asio::buffer(data), error);
                        if (!error) {
                            std::cout << "Received: " << std::string(data, len) << std::endl;
                        }
                    } catch (const std::exception& e) {
                        std::cerr << "Exception in client thread: " << e.what() << std::endl;
                    }
                }).detach();
            } else {
                std::cerr << "Accept error: " << ec.message() << std::endl;
            }
            Accept(); // Continue accepting new connections
        });
    }

    tcp::acceptor acceptor_;
};

class TcpClient {
public:
    TcpClient(boost::asio::io_context& io_context,
              const std::string& host,
              const std::string& port)
        : resolver_(io_context), socket_(io_context) {
        Connect(host, port);
    }

    void Send(const std::string& message) {
        boost::asio::write(socket_, boost::asio::buffer(message));
    }

private:
    void Connect(const std::string& host, const std::string& port) {
        auto endpoints = resolver_.resolve(host, port);
        boost::asio::connect(socket_, endpoints);
    }

    tcp::resolver resolver_;
    tcp::socket socket_;
};

} // namespace unilib::boost_utils
