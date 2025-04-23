# unilib++ Setup Guide

This document helps you set up the `unilib++` library on your system.

---

## ✅ Prerequisites

- CMake ≥ 3.15
- C++17 compiler (GCC, Clang, MSVC)
- Git
- Optional: vcpkg (for dependency management)
- Optional: Python3 (for scripting or advanced build steps)

---

## 🛠 Build (Linux/macOS)

```bash
git clone https://github.com/your-org/unilibpp.git
cd unilibpp
chmod +x scripts/clean.sh scripts/build.sh
./scripts/clean.sh
./scripts/build.sh
