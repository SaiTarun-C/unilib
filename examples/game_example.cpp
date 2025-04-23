#include <games/opengl.hpp>
#include <games/sfml.hpp>
#include <iostream>

int main() {
    // OpenGL Example
    try {
        auto window = unilib::games::OpenGLContext::init(800, 600, "OpenGL Window");

        unilib::games::OpenGLContext::renderLoop(window.get(), []() {
            // OpenGL rendering code here
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set background color
            glClear(GL_COLOR_BUFFER_BIT);
        });

    } catch (const std::exception& e) {
        std::cerr << "OpenGL Error: " << e.what() << std::endl;
    }

    // SFML Example
    try {
        unilib::games::SFMLApp app(800, 600, "SFML Window");
        app.setRenderFunction([](sf::RenderWindow& window) {
            // SFML rendering code here
            sf::CircleShape shape(50);
            shape.setFillColor(sf::Color::Green);
            shape.setPosition(375.f, 275.f);
            window.draw(shape);
        });

        app.run();

    } catch (const std::exception& e) {
        std::cerr << "SFML Error: " << e.what() << std::endl;
    }

    return 0;
}
