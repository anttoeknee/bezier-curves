

#include "Logo.hpp"

#include "SFML/Graphics/RectangleShape.hpp"

ui::elements::Logo::Logo(std::vector<common::Point> &&startPoints_)
    : startPoints(std::move(startPoints_)) {

    // convert to control point shapes
    for (auto &point: startPoints) {
        sf::RectangleShape rect(sf::Vector2f(point.size.x, point.size.y));
        rect.setPosition({point.position.x, point.position.y});
        rect.setFillColor(sf::Color::White);
        controlPoints.push_back(std::make_unique<sf::RectangleShape>(rect));
    }

}

void ui::elements::Logo::draw(sf::RenderWindow &target, sf::Vector2f origin) const {
    // Control points
    for (auto &controlPoint: controlPoints) {
        target.draw(*controlPoint);
    }
}

void ui::elements::Logo::update(sf::RenderWindow &target, sf::Vector2f origin) const {

}

void ui::elements::Logo::handleMouseMove(sf::Vector2f &mousePos) {

}

void ui::elements::Logo::handleMouseButtonPressed(sf::Vector2f &mousePos) {

}

void ui::elements::Logo::handleMouseButtonReleased() {

}