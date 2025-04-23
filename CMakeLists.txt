cmake_minimum_required(VERSION 3.14)
project(unilibpp VERSION 1.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set toolchain if needed (if not passed via command line)
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND EXISTS "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
    set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)

# Packaging
include(CPack)

set(CPACK_PACKAGE_NAME "unilibpp")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_GENERATOR "ZIP;TGZ")
set(CPACK_PACKAGE_CONTACT "you@example.com")

# Find jsoncpp package
find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(unilibpp PRIVATE jsoncpp_lib)

# Find CURL package
find_package(CURL REQUIRED)
target_link_libraries(unilibpp PRIVATE CURL::libcurl)

# WebSocket++ setup
# Include WebSocket++ headers manually since it doesn't have a cmake config file
include_directories("C:/Users/saita/Documents/coding_practice/cpp/unilib/include/net")

# WebSocket++ does not require an explicit linking to a library file, 
# it's a header-only library, so it's sufficient to just include the headers
# No need to link websocketpp as it's header-only

# Example CMakeLists.txt for your WebSocketExample project
cmake_minimum_required(VERSION 3.10)
project(WebSocketExample)

# Add the include directory where WebSocket++ is located
include_directories("C:/Users/saita/Documents/coding_practice/cpp/unilib/include/net")

# Add your source files
add_executable(WebSocketExample src/main.cpp)

# Link any additional libraries (like Boost, Asio, etc.) here if needed
# target_link_libraries(WebSocketExample Boost::Boost)
