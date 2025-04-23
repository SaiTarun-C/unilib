#include "core/logger.hpp"
#include <fstream>
#include <iostream>
#include <mutex>
#include <ctime>
#include <chrono>
#include <iomanip>

namespace unilib::core {

Logger::Logger(LogLevel level, const std::string& log_file)
    : log_level_(level), log_file_(log_file) {}

void Logger::Log(LogLevel level, const std::string& message, const std::string& file, int line, const std::string& function) {
    if (level < log_level_) return; // Skip logs below the current log level

    std::lock_guard<std::mutex> lock(mutex_);

    // Get current time for timestamp
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm local_time;
    localtime_s(&local_time, &now);
    std::stringstream timestamp;
    timestamp << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");

    // Format the log message
    std::stringstream log_msg;
    log_msg << "[" << timestamp.str() << "] "
            << "[" << LogLevelToString(level) << "] "
            << "[" << file << ":" << line << "] "
            << "[" << function << "] "
            << message;

    // Output to console
    if (console_output_) {
        std::cout << log_msg.str() << std::endl;
    }

    // Output to file
    if (!log_file_.empty()) {
        std::ofstream log_stream(log_file_, std::ios_base::app);
        if (log_stream.is_open()) {
            log_stream << log_msg.str() << std::endl;
        } else {
            std::cerr << "Error opening log file: " << log_file_ << std::endl;
        }
    }
}

std::string Logger::LogLevelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::Trace: return "TRACE";
        case LogLevel::Debug: return "DEBUG";
        case LogLevel::Info: return "INFO";
        case LogLevel::Warning: return "WARNING";
        case LogLevel::Error: return "ERROR";
        case LogLevel::Critical: return "CRITICAL";
        default: return "UNKNOWN";
    }
}

void Logger::SetLogLevel(LogLevel level) {
    log_level_ = level;
}

void Logger::EnableConsoleOutput(bool enable) {
    console_output_ = enable;
}

} // namespace unilib::core
