#include "std/string.hpp"
#include <algorithm>
#include <cctype>
#include <string>
#include <stdexcept>
#include <sstream>

namespace unilib::std_utils {

// Function to trim whitespace from the beginning and end of a string
std::string Trim(const std::string& str) {
    auto start = str.find_first_not_of(" \t\n\r\f\v");
    auto end = str.find_last_not_of(" \t\n\r\f\v");

    if (start == std::string::npos || end == std::string::npos) {
        return "";
    }

    return str.substr(start, end - start + 1);
}

// Function to convert a string to lowercase
std::string ToLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::tolower(c); });
    return result;
}

// Function to convert a string to uppercase
std::string ToUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });
    return result;
}

// Function to split a string by a delimiter and return a vector of substrings
std::vector<std::string> Split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to safely get a substring within bounds (returns empty if out of bounds)
std::string SafeSubstr(const std::string& str, size_t pos, size_t len) {
    if (pos > str.size()) {
        throw std::out_of_range("Starting position is out of range");
    }
    return str.substr(pos, len);
}

} // namespace unilib::std_utils
