#include "games/opengl.hpp"
#include <iostream>
#include <stdexcept>

namespace unilib::games {

OpenGLRenderer::OpenGLRenderer() {}

OpenGLRenderer::~OpenGLRenderer() {
    cleanup();
}

bool OpenGLRenderer::initialize() {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        lastError_ = reinterpret_cast<const char*>(glewGetErrorString(err));
        return false;
    }
    return setup();
}

bool OpenGLRenderer::setup() {
    // Define triangle vertices
    GLfloat vertices[] = {
        0.0f,  0.5f, // Top
       -0.5f, -0.5f, // Left
        0.5f, -0.5f  // Right
    };

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

void OpenGLRenderer::render() {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void OpenGLRenderer::cleanup() {
    if (vbo_) glDeleteBuffers(1, &vbo_);
    if (vao_) glDeleteVertexArrays(1, &vao_);
    vbo_ = vao_ = 0;
}

const std::string& OpenGLRenderer::lastError() const {
    return lastError_;
}

} // namespace unilib::games
