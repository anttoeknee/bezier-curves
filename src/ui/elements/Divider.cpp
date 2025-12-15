
#include "Divider.hpp"

#include "SFML/Graphics/RectangleShape.hpp"

void ui::elements::Divider::draw(sf::RenderWindow &target, sf::Vector2f origin) {
    target.draw(line);
}

void ui::elements::Divider::update(sf::RenderWindow &target, sf::Vector2f origin) {
    // TODO: find way to pass values in
    line = sf::RectangleShape({1080, 1.f});
    line.setPosition({0, 401});
    line.setFillColor(sf::Color(150, 150, 150));
}

void ui::elements::Divider::handleMouseMove(sf::Vector2f &mousePos) {
}

void ui::elements::Divider::handleMouseButtonPressed(sf::Vector2f &mousePos) {
}

void ui::elements::Divider::handleMouseButtonReleased() {
}

ui::elements::Divider::Divider() = default;
