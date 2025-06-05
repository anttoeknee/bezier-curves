
#include "Divider.hpp"

#include "SFML/Graphics/RectangleShape.hpp"

void Divider::draw(sf::RenderWindow &target, sf::Vector2f origin) const {
    target.draw(line);
}

void Divider::update(sf::RenderWindow &target, sf::Vector2f origin) const {
    // TODO: find way to pass values in
    line = sf::RectangleShape({1080, 1.f});
    line.setPosition({0, 401});
    line.setFillColor(sf::Color(150, 150, 150));
}

void Divider::handleMouseButtonPressed(sf::Vector2i &mousePos) {
}

void Divider::handleMouseButtonReleased() {
}

Divider::Divider() = default;
