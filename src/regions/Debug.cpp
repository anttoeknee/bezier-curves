

#include "Debug.hpp"
#include "../elements/Metrics.hpp"

Debug::Debug() {
    position = {1080, 0};
    size = {200, 800};

    // Mem usage, mouse position etc
    elements.push_back(std::make_unique<Metrics>());
}

void Debug::draw(sf::RenderWindow &target) const {
    target.draw(container);

    for (auto &element : elements) {
        element->draw(target, position);
    }
}

void Debug::update(sf::RenderWindow &target) const {

    container = sf::RectangleShape(size);
    container.setPosition(position);
    container.setFillColor(sf::Color::White);

    for (auto &element : elements) {
        element->update(target, position);
    }
}

void Debug::handleMouseButtonPressed(sf::Vector2i &mousePos) {
    for (auto &element : elements) {
        element->handleMouseButtonPressed(mousePos);
    }
}

void Debug::handleMouseButtonReleased() {
    for (auto &element : elements) {
        element->handleMouseButtonReleased();
    }
}

