#include "net/http.hpp"
#include "httplib.h"  // You must place this in your include path
#include <iostream>
#include <stdexcept>

namespace unilib::net {

std::string HttpClient::Get(const std::string& host, int port, const std::string& path) {
    try {
        httplib::Client client(host, port);
        auto res = client.Get(path.c_str());
        if (res && res->status == 200) {
            return res->body;
        } else {
            throw std::runtime_error("HTTP GET failed with status: " + std::to_string(res ? res->status : 0));
        }
    } catch (const std::exception& e) {
        std::cerr << "[HTTP GET ERROR] " << e.what() << std::endl;
        return {};
    }
}

std::string HttpClient::Post(const std::string& host, int port, const std::string& path, const std::string& body, const std::string& content_type) {
    try {
        httplib::Client client(host, port);
        auto res = client.Post(path.c_str(), body, content_type.c_str());
        if (res && res->status == 200) {
            return res->body;
        } else {
            throw std::runtime_error("HTTP POST failed with status: " + std::to_string(res ? res->status : 0));
        }
    } catch (const std::exception& e) {
        std::cerr << "[HTTP POST ERROR] " << e.what() << std::endl;
        return {};
    }
}

}  // namespace unilib::net
