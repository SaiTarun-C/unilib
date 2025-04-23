//Purpose: Parses and manipulates JSON data.

#include <iostream>
#include <nlohmann/json.hpp>

int main() {
    std::string json_text = R"({
        "name": "unilib++",
        "version": 1.0,
        "features": ["logging", "config", "networking"]
    })";

    try {
        auto json_data = nlohmann::json::parse(json_text);
        std::cout << "Project Name: " << json_data["name"] << std::endl;
        std::cout << "Version: " << json_data["version"] << std::endl;
        std::cout << "Features:\n";
        for (const auto& feature : json_data["features"]) {
            std::cout << "- " << feature << std::endl;
        }
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON Parse Error: " << e.what() << std::endl;
    }

    return 0;
}
