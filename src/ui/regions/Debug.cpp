

#include "Debug.hpp"
#include "../elements/Metrics.hpp"

ui::regions::Debug::Debug(sf::RenderWindow &target): Region(target) {
    position = {1080, 0};
    size = {200, 800};

    // Mem usage, mouse position etc
    elements.push_back(std::make_unique<elements::Metrics>());
}

void ui::regions::Debug::draw() const {
    target.draw(container);

    for (auto &element : elements) {
        element->draw(target, position);
    }
}

void ui::regions::Debug::update() const {

    container = sf::RectangleShape(size);
    container.setPosition(position);
    container.setFillColor(sf::Color::White);

    for (auto &element : elements) {
        element->update(target, position);
    }
}

void ui::regions::Debug::handleMouseMove(sf::Vector2f &mousePos) {
    for (auto &element : elements) {
        element->handleMouseMove(mousePos);
    }
}

void ui::regions::Debug::handleMouseButtonPressed(sf::Vector2f &mousePos) {
    for (auto &element : elements) {
        element->handleMouseButtonPressed(mousePos);
    }
}

void ui::regions::Debug::handleMouseButtonReleased() {
    for (auto &element : elements) {
        element->handleMouseButtonReleased();
    }
}

