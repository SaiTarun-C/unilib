# 🏛️ unilib++ Architecture Overview

The `unilib++` library is designed to be a modular, cross-platform, high-performance C++ utility library. Its architecture is built with a focus on flexibility, scalability, and reusability. This document provides a high-level overview of the architecture, key modules, and their relationships.

---

## 🌟 Key Design Principles

- **Modularity**: Each major functionality is grouped into independent modules, allowing easy integration, replacement, and maintenance.
- **Cross-Platform**: The library is built to work seamlessly across various platforms (Windows, Linux, macOS) without depending on platform-specific tools or libraries like Qt.
- **Efficiency**: Performance is a primary concern, with optimized implementations for core utilities such as logging, threading, and networking.
- **Extensibility**: The design anticipates future expansions, supporting additional features such as machine learning integrations, advanced networking protocols, and more.

---

## 🗂️ High-Level Architecture

The `unilib++` library is organized into several top-level modules, each providing a set of utilities or features:

1. **Core**
   - **Logger**: A high-performance, thread-safe logging utility with support for different log levels (INFO, DEBUG, ERROR) and customizable output formats.
   - **Config**: Provides platform and compiler-specific configurations, enabling smooth operation across various development environments.

2. **Standard Library Extensions**
   - **Vector Utilities**: Enhancements to the standard `std::vector`, including operations like printing, reversing, and more.
   - **String Utilities**: Extensions to `std::string`, including trimming, case conversion, and other string manipulations.
   - **Algorithm Extensions**: Custom algorithms and utility functions that extend the standard library algorithms (e.g., summing elements in a container).

3. **Networking**
   - **HTTP Client**: A simple wrapper around the HTTP protocol for making requests and handling responses asynchronously.
   - **WebSocket**: A wrapper for WebSocket connections, supporting both client and server operations.

4. **Filesystem**
   - **Filesystem Utilities**: Functions for working with directories, files, and paths, supporting both standard file system operations and more advanced tasks like recursive searching.

5. **Data**
   - **JSON**: A lightweight wrapper around the `nlohmann/json` library for parsing and working with JSON data.
   - **XML**: A wrapper for XML processing, enabling parsing, serialization, and manipulation of XML documents.

6. **Machine Learning**
   - **TensorFlow**: Integration with the TensorFlow C++ API for running machine learning models and performing inference.
   - **Dlib**: Integration with the Dlib library for tasks like face detection and machine learning.

7. **GUI**
   - **ImGui**: An immediate-mode GUI library that allows rapid prototyping of graphical user interfaces with minimal setup.
   - **SDL**: Integration with Simple DirectMedia Layer (SDL) for creating games and multimedia applications.

8. **Plugin System**
   - **Plugin Manager**: A flexible plugin architecture that allows dynamic loading and unloading of shared libraries, enabling extendable functionality.

9. **System Utilities**
   - **Threading**: Utilities for multithreading and synchronization, supporting various synchronization primitives like mutexes and condition variables.
   - **OS Utilities**: Functions for interacting with the operating system, including environment variable retrieval and user-specific data.

10. **Games**
    - **OpenGL**: Wrappers for OpenGL functionality, allowing for easy integration into graphics or game projects.
    - **SFML**: Wrappers around SFML (Simple and Fast Multimedia Library) for 2D game development and multimedia applications.

---

## 🔗 Module Interconnections

The modules in `unilib++` are designed to be loosely coupled and independent, but they do interact in several ways:

1. **Core Dependencies**
   - The `Logger` module is a fundamental part of the library and is often used across different modules for logging purposes.
   - The `Config` module is primarily used to gather platform-specific configurations, ensuring that the library works seamlessly across different environments.

2. **Networking & Data Parsing**
   - The `HTTP Client` and `WebSocket` modules are often used together in scenarios where the application needs to communicate over the web.
   - The `JSON` and `XML` modules are essential when dealing with data parsing and serialization. These modules are typically used in conjunction with networking modules for API interactions.

3. **Machine Learning and Data Processing**
   - The `TensorFlow` and `Dlib` modules interact closely with data modules, especially for data preprocessing and feature extraction tasks in machine learning workflows.

4. **Games and Graphics**
   - The `OpenGL` and `SFML` modules are part of the `Games` module, allowing for the development of graphical applications or games. These modules can be combined with threading and OS utilities to provide high-performance game loops.

5. **Plugin System**
   - The `Plugin Manager` is designed to be an extensible system where external functionality can be dynamically loaded. It integrates with various other modules, especially for use cases that require runtime extensibility.

---

## 🛠️ Module Interactions Example

### Core Logger + Networking (HTTP)

```cpp
#include "core/logger.hpp"
#include "net/http.hpp"

int main() {
    UNILOG_INIT();

    // HTTP request
    std::string response = unilib::net::http_get("https://httpbin.org/get");

    // Log the response
    UNILOG_INFO("Received response: {}", response);

    return 0;
}
