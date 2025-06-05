#include "Bezier.hpp"
#include "../elements/QuadraticBezier.hpp"
#include "../elements/Metrics.hpp"
#include "../elements/Divider.hpp"
#include "../utils/ScopedWindowClipping.hpp"

Bezier::Bezier(sf::RenderWindow &target): Region(target) {
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

Bezier::~Bezier() = default;


void Bezier::handleMouseButtonPressed(sf::Vector2f &mousePos) {
    sf::Vector2f localMouse = mousePos - position;
    for (auto &element : elements) {
        element->handleMouseButtonPressed(localMouse);
    }
}

void Bezier::handleMouseButtonReleased() {
    for (auto &element : elements) {
        element->handleMouseButtonReleased();
    }
}

void Bezier::draw() const {

    sf::Vector2f windowSize = static_cast<sf::Vector2f>(target.getSize());

    sf::View oldView = target.getView();

    ui::utils::ScopedWindowClipping clip(target, position, windowSize);

    sf::RectangleShape background;
    background.setPosition(position);
    background.setSize(size);
    background.setFillColor(sf::Color(50, 50, 50)); // Dark gray background

    target.draw(background);

    for (auto &element : elements) {
        element->draw(target, position);
    }

    target.setView(oldView);
}

void Bezier::update() const {
    for (auto &element : elements) {
        element->update(target, position);
    }
}





