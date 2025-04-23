::Purpose: Build unilib++ on Windows using CMake + MSVC or MinGW.

@echo off
setlocal enabledelayedexpansion

set BUILD_DIR=build

if not exist %BUILD_DIR% (
    mkdir %BUILD_DIR%
)

cd %BUILD_DIR%

:: Configure with CMake
echo Configuring project...
cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release

:: Build the project
if errorlevel 1 (
    echo Configuration failed.
    exit /b 1
)

echo Building project...
nmake

if errorlevel 1 (
    echo Build failed.
    exit /b 1
)

echo Build completed successfully!
