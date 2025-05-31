#include "Bezier.hpp"
#include "../elements/QuadraticBezier.hpp"
#include "../elements/Debug.hpp"

Bezier::Bezier() {

    std::vector<PointData> startPoints = {
        {"Point 1", {200, 400}, {15, 15}},
        {"Point 2", {500, 100}, {15, 15}},
        {"Point 3", {1000, 275}, {15, 15}}
    };

    elements.push_back(std::make_unique<QuadraticBezier>(std::move(startPoints)));
    elements.push_back(std::make_unique<Debug>());
}

void Bezier::handleMouseButtonPressed(sf::Vector2i &mousePos) {
    for (auto &element : elements) {
        element->handleMouseButtonPressed(mousePos);
    }
}

void Bezier::handleMouseButtonReleased() {
    for (auto &element : elements) {
        element->handleMouseButtonReleased();
    }
}

void Bezier::draw(sf::RenderWindow &target) const {
    for (auto &element : elements) {
        element->draw(target);
    }
}

void Bezier::update(sf::RenderWindow &target) const {
    for (auto &element : elements) {
        element->update(target);
    }
}





