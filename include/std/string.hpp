#ifndef UNILIB_STD_STRING_HPP
#define UNILIB_STD_STRING_HPP

#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cctype>
#include <locale>

namespace unilib::std_ext::str {

// Trim leading and trailing whitespace
inline std::string trim(const std::string& s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) ++start;

    auto end = s.end();
    do { --end; } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

// Split string by delimiter
inline std::vector<std::string> split(const std::string& str, char delimiter = ' ') {
    std::vector<std::string> tokens;
    std::istringstream stream(str);
    std::string tok;
    while (std::getline(stream, tok, delimiter)) {
        if (!tok.empty())
            tokens.push_back(tok);
    }
    return tokens;
}

// Join vector into string
inline std::string join(const std::vector<std::string>& tokens, const std::string& delimiter = " ") {
    std::ostringstream oss;
    for (std::size_t i = 0; i < tokens.size(); ++i) {
        if (i != 0) oss << delimiter;
        oss << tokens[i];
    }
    return oss.str();
}

// Convert to lowercase
inline std::string to_lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return s;
}

// Convert to uppercase
inline std::string to_upper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return s;
}

} // namespace unilib::std_ext::str

#endif // UNILIB_STD_STRING_HPP
