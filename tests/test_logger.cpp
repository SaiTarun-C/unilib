#include <gtest/gtest.h>
#include "logger.hpp"
#include <sstream>
#include <chrono>

TEST(LoggerTest, LogMessages) {
    std::ostringstream log_stream;
    Logger logger(log_stream);

    // Log info message
    logger.info("Test info message");
    EXPECT_NE(log_stream.str().find("INFO"), std::string::npos);

    // Log error message
    log_stream.str("");  // Clear the stream
    logger.error("Test error message");
    EXPECT_NE(log_stream.str().find("ERROR"), std::string::npos);

    // Check log format
    auto current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string time_str = std::ctime(&current_time);
    EXPECT_NE(log_stream.str().find(time_str), std::string::npos);
}

TEST(LoggerTest, LogLevels) {
    std::ostringstream log_stream;
    Logger logger(log_stream);

    logger.setLogLevel(LogLevel::Warning);

    // Log an info message (should not appear)
    logger.info("Info message");
    EXPECT_EQ(log_stream.str(), "");

    // Log a warning message (should appear)
    logger.warning("Warning message");
    EXPECT_NE(log_stream.str().find("WARNING"), std::string::npos);
}
