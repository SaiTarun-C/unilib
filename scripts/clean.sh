#!/bin/bash

echo "Cleaning build files..."

rm -rf build/
rm -rf CMakeFiles/
rm -f CMakeCache.txt cmake_install.cmake Makefile

echo "Clean completed."
