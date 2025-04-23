# src/CMakeLists.txt

# Include headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Create the main static library
add_library(unilibpp STATIC
    core/logger.cpp
    core/config.cpp
    #core/vector.cpp
    #core/string.cpp
    net/http.cpp
    net/websocket.cpp
    fs/filesystem_utils.cpp
    sys/threading.cpp
    sys/os_utils.cpp
    data/json.cpp
    data/xml.cpp
    games/opengl.cpp
    games/sfml.cpp
    meta/type_traits.cpp
    plugin/plugin_manager.cpp
)

