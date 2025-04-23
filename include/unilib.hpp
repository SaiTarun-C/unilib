#ifndef UNILIB_HPP
#define UNILIB_HPP

// Core Utilities
#include "core/logger.hpp"
#include "core/config.hpp"

// STL Extensions
#include "std/algorithm.hpp"
#include "std/vector.hpp"
#include "std/string.hpp"

// Boost Wrappers
#include "boost/filesystem.hpp"
#include "boost/asio.hpp"

// Networking
#include "net/http.hpp"
#include "net/websocket.hpp"

// GUI Abstraction
#include "gui/imgui.hpp"
#include "gui/sdl.hpp"

// Machine Learning
#include "ml/tensorflow.hpp"
#include "ml/dlib.hpp"

// Filesystem
#include "fs/filesystem_utils.hpp"

// System Utils
#include "sys/threading.hpp"
#include "sys/os_utils.hpp"

// Data Format Support
#include "data/json.hpp"
#include "data/xml.hpp"

// Game Development
#include "games/opengl.hpp"
#include "games/sfml.hpp"

// Metaprogramming
#include "meta/type_traits.hpp"

// Plugin Support
#include "plugin/plugin_manager.hpp"

#endif // UNILIB_HPP
