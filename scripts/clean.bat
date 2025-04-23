@echo off
echo Cleaning build files...

rmdir /s /q build
del /q CMakeCache.txt
del /q cmake_install.cmake
del /q Makefile
rmdir /s /q CMakeFiles

echo Clean completed.
pause
