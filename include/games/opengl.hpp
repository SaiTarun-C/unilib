#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <memory>

namespace unilib::games {

class OpenGLContext {
public:
    static std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> init(int width, int height, const std::string& windowTitle) {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        GLFWwindow* window = glfwCreateWindow(width, height, windowTitle.c_str(), nullptr, nullptr);

        if (!window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(window);
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            throw std::runtime_error("Failed to initialize GLEW");
        }

        return std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)>(window, glfwDestroyWindow);
    }

    static void checkOpenGLError() {
        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << err << std::endl;
        }
    }

    static void renderLoop(GLFWwindow* window, const std::function<void()>& renderFunc) {
        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            renderFunc();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
};

} // namespace unilib::games
