//Purpose: Implements a basic SFML window with a moving circle.


#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game Demo");
    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Green);
    float speed = 100.f;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        circle.move(speed * deltaTime, 0.f);
        if (circle.getPosition().x > window.getSize().x)
            circle.setPosition(0.f, circle.getPosition().y);

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}
