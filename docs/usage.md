# 📘 unilib++ Usage Examples

This document provides simple and clear examples for each major module of the `unilib++` library.

---

## 🔧 Core Logger

```cpp
#include "core/logger.hpp"

int main() {
    UNILOG_INIT();
    UNILOG_INFO("Logger initialized successfully!");
    UNILOG_DEBUG("Debugging is enabled.");
    UNILOG_ERROR("Something went wrong!");
    return 0;
}
