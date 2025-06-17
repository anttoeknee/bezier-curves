

#include "Debug.hpp"
#include "../elements/Metrics.hpp"

ui::regions::Debug::Debug(sf::RenderWindow &target, std::vector<std::unique_ptr<elements::Element> > &&elements, sf::Vector2f position, sf::Vector2f size): Region(target, std::move(elements)) {
    _position = position;
    _size = size;
}

void ui::regions::Debug::draw() const {
    target.draw(container);

    for (auto &element : elements) {
        element->draw(target, _position);
    }
}

void ui::regions::Debug::update() const {

    container = sf::RectangleShape(_size);
    container.setPosition(_position);
    container.setFillColor(sf::Color::White);

    for (auto &element : elements) {
        element->update(target, _position);
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

