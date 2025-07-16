#include <vector>

#include "Element.hpp"
#include "QuadraticBezier.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "../../core/math/Geometry.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Window/Mouse.hpp"


ui::elements::QuadraticBezier::QuadraticBezier(const std::vector<common::Point>& startPoints) : startPoints(startPoints) {

    // Initial state
    for (auto &point: startPoints) {
        sf::RectangleShape rect(sf::Vector2f(point.size.x, point.size.y));
        rect.setPosition({point.position.x, point.position.y});
        rect.setFillColor(sf::Color::White);
        controlPoints.push_back(std::make_unique<sf::RectangleShape>(rect));
    }
}

void ui::elements::QuadraticBezier::draw(sf::RenderWindow &target, sf::Vector2f origin) const {
    // Control points
    for (auto &controlPoint: controlPoints) {
        target.draw(*controlPoint);
    }

    // Lines
    std::vector<sf::Vertex> bezierLine;
    for (float t = 0; t <= 1.0f; t += 0.01f) {
        sf::Vector2f point = core::math::quadraticBezier(
            controlPoints[0]->getPosition(),
            controlPoints[1]->getPosition(),
            controlPoints[2]->getPosition(),
            t
        );
        bezierLine.push_back(sf::Vertex({point, sf::Color::White}));
    }

    target.draw(&bezierLine[0], bezierLine.size(), sf::PrimitiveType::LineStrip);
}

void ui::elements::QuadraticBezier::update(sf::RenderWindow &target, sf::Vector2f origin) const {
    // Handle dragging
    if (isDragging && draggedShape) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(target);
        draggedShape->setPosition({mousePos.x - dragOffset.x, mousePos.y - dragOffset.y});
    }
}

void ui::elements::QuadraticBezier::handleMouseMove(sf::Vector2f &mousePos) {

}


void ui::elements::QuadraticBezier::handleMouseButtonPressed(sf::Vector2f &mousePos) {
    for (auto &controlPoint: controlPoints) {
        // Determine if we've mouse-downed on this shape
        if (controlPoint->getGlobalBounds().contains(mousePos)) {
            // Update our bool
            isDragging = true;

            // Make sure we don't get jumpy movement of the shape
            draggedShape = controlPoint.get();
            dragOffset = mousePos - draggedShape->getPosition();

            break;
        }
    }
}

void ui::elements::QuadraticBezier::handleMouseButtonReleased() {
    // Reset our bool and dragged shape
    isDragging = false;
    draggedShape = nullptr;
}
