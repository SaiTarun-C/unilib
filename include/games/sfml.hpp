#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <functional>
#include <iostream>
#include <stdexcept>

namespace unilib::games {

class SFMLApp {
public:
    SFMLApp(int width, int height, const std::string& windowTitle) {
        window.create(sf::VideoMode(width, height), windowTitle);
        if (!window.isOpen()) {
            throw std::runtime_error("Failed to open SFML window");
        }
    }

    void setRenderFunction(const std::function<void(sf::RenderWindow&)>& renderFunc) {
        renderFunc_ = renderFunc;
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear();
            renderFunc_(window);
            window.display();
        }
    }

private:
    sf::RenderWindow window;
    std::function<void(sf::RenderWindow&)> renderFunc_;
};

} // namespace unilib::games
