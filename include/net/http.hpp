// File: include/net/http.hpp
#ifndef UNILIB_NET_HTTP_HPP
#define UNILIB_NET_HTTP_HPP

#include <string>
#include <map>
#include <stdexcept>
#include <sstream>
#include <curl/curl.h>

namespace unilib::net {

class HttpClient {
public:
    HttpClient() {
        curl_global_init(CURL_GLOBAL_ALL);
    }

    ~HttpClient() {
        curl_global_cleanup();
    }

    std::string get(const std::string& url, const std::map<std::string, std::string>& headers = {}) {
        return request("GET", url, "", headers);
    }

    std::string post(const std::string& url, const std::string& data,
                     const std::map<std::string, std::string>& headers = {}) {
        return request("POST", url, data, headers);
    }

private:
    static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    std::string request(const std::string& method, const std::string& url,
                        const std::string& data,
                        const std::map<std::string, std::string>& headers) {
        CURL* curl = curl_easy_init();
        if (!curl) throw std::runtime_error("Failed to initialize CURL");

        std::string response;
        struct curl_slist* chunk = nullptr;

        for (const auto& h : headers) {
            chunk = curl_slist_append(chunk, (h.first + ": " + h.second).c_str());
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        if (!data.empty()) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        }

        if (chunk) curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            curl_slist_free_all(chunk);
            curl_easy_cleanup(curl);
            throw std::runtime_error("CURL request failed: " + std::string(curl_easy_strerror(res)));
        }

        curl_slist_free_all(chunk);
        curl_easy_cleanup(curl);

        return response;
    }
};

} // namespace unilib::net

#endif // UNILIB_NET_HTTP_HPP