#Purpose: Build unilib++ on Linux/macOS systems. Handles dependencies, out-of-source build, and flags.

#!/bin/bash

set -e

# Define build directory
BUILD_DIR="build"

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
  mkdir "$BUILD_DIR"
fi

# Navigate to build directory
cd "$BUILD_DIR"

# Configure with CMake
echo "Configuring project..."
cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Build with make or ninja
echo "Building project..."
if command -v ninja &> /dev/null; then
  cmake --build . -- -j$(nproc)
else
  make -j$(nproc)
fi

echo "Build completed successfully!"
