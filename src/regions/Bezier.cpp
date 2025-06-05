#include "Bezier.hpp"
#include "../elements/QuadraticBezier.hpp"
#include "../elements/Metrics.hpp"
#include "../elements/Divider.hpp"

Bezier::Bezier() {

    position = {0, 0};
    size = {1080, 800};

    std::vector<PointData> startPoints = {
        {"Point 1", {50, 350}, {15, 15}},
        {"Point 2", {350, 50}, {15, 15}},
        {"Point 3", {850, 275}, {15, 15}}
    };

    elements.push_back(std::make_unique<Divider>());
    elements.push_back(std::make_unique<QuadraticBezier>(std::move(startPoints)));
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

    //sf::View oldView = target.getView();

    sf::RectangleShape background;
    background.setPosition(position);
    background.setSize(size);
    background.setFillColor(sf::Color(50, 50, 50)); // Dark gray background

    target.draw(background);

    //sf::View clipView(position + size * 0.5f, size); // sf::View is center-based
    //target.setView(clipView);

    for (auto &element : elements) {
        element->draw(target, position);
    }

    //target.setView(oldView);
}

void Bezier::update(sf::RenderWindow &target) const {
    for (auto &element : elements) {
        element->update(target, position);
    }
}





