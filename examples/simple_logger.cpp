//Purpose: Demonstrates logging with different levels and outputs.

#include "logger.hpp"

int main() {
    Logger logger;
    logger.setLogLevel(LogLevel::Debug);

    logger.info("Application started.");
    logger.debug("Debugging information.");
    logger.warning("This is a warning.");
    logger.error("An error occurred.");

    return 0;
}
