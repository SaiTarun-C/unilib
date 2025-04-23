# tests/CMakeLists.txt

# Use modern CMake GTest config
find_package(GTest REQUIRED CONFIG)

# Add executable for all tests
add_executable(unilibpp_tests
    test_logger.cpp
    test_config.cpp
    test_vector.cpp
    test_string.cpp
    test_http.cpp
    test_websocket.cpp
    test_filesystem.cpp
    test_plugin.cpp
)

# Link unilibpp library + GTest libraries
target_link_libraries(unilibpp_tests
    PRIVATE
        unilibpp
        GTest::gtest
        GTest::gtest_main
)

# Enable test discovery with CTest
include(GoogleTest)
gtest_discover_tests(unilibpp_tests)
