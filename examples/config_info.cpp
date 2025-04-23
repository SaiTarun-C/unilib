//Purpose: Displays OS and compiler information.

#include <iostream>

int main() {
    std::cout << "Operating System: ";
#if defined(_WIN32)
    std::cout << "Windows";
#elif defined(__linux__)
    std::cout << "Linux";
#elif defined(__APPLE__)
    std::cout << "macOS";
#else
    std::cout << "Unknown OS";
#endif
    std::cout << std::endl;

    std::cout << "Compiler: ";
#if defined(__clang__)
    std::cout << "Clang";
#elif defined(__GNUC__)
    std::cout << "GCC";
#elif defined(_MSC_VER)
    std::cout << "MSVC";
#else
    std::cout << "Unknown Compiler";
#endif
    std::cout << std::endl;

    return 0;
}
