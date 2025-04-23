#pragma once

#include <string>
#include <mutex>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>

namespace unilib::core {

enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Critical
};

class Logger {
public:
    Logger(LogLevel level = LogLevel::Info, const std::string& log_file = "");

    // Log a message
    void Log(LogLevel level, const std::string& message, const std::string& file, int line, const std::string& function);

    // Set log level
    void SetLogLevel(LogLevel level);

    // Enable/Disable console output
    void EnableConsoleOutput(bool enable);

private:
    std::string LogLevelToString(LogLevel level) const;

    LogLevel log_level_;
    std::string log_file_;
    bool console_output_ = true;
    std::mutex mutex_;
};

} // namespace unilib::core
