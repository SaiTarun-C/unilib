#include "games/sfml.hpp"
#include <iostream>

namespace unilib::games {

SFMLGame::SFMLGame() : window_(nullptr) {}

SFMLGame::~SFMLGame() {
    cleanup();
}

bool SFMLGame::initialize(unsigned width, unsigned height, const std::string& title) {
    window_ = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
    if (!window_) {
        lastError_ = "Failed to create SFML window.";
        return false;
    }

    shape_.setRadius(50.f);
    shape_.setFillColor(sf::Color::Green);
    shape_.setPosition(100.f, 100.f);
    return true;
}

void SFMLGame::run() {
    if (!window_) return;

    while (window_->isOpen()) {
        sf::Event event;
        while (window_->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_->close();
            }
        }

        window_->clear(sf::Color::Black);
        window_->draw(shape_);
        window_->display();
    }
}

void SFMLGame::cleanup() {
    if (window_ && window_->isOpen()) {
        window_->close();
    }
    window_.reset();
}

const std::string& SFMLGame::lastError() const {
    return lastError_;
}

} // namespace unilib::games
