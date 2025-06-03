#include "Bezier.hpp"
#include "../elements/QuadraticBezier.hpp"
#include "../elements/Debug.hpp"
#include "../elements/Divider.hpp"

Bezier::Bezier() {

    x = 0;
    y = 0;
    width = 1080;
    height = 800;

    std::vector<PointData> startPoints = {
        {"Point 1", {50, 350}, {15, 15}},
        {"Point 2", {350, 50}, {15, 15}},
        {"Point 3", {850, 275}, {15, 15}}
    };

    elements.push_back(std::make_unique<Divider>());
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

    sf::RectangleShape background;
    background.setPosition({x, y});
    background.setSize({width, height});
    background.setFillColor(sf::Color(50, 50, 50)); // Dark gray background

    target.draw(background);

    for (auto &element : elements) {
        element->draw(target);
    }
}

void Bezier::update(sf::RenderWindow &target) const {
    for (auto &element : elements) {
        element->update(target);
    }
}





