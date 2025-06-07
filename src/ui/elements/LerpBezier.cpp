#include "LerpBezier.hpp"

#include <vector>

#include "Element.hpp"
#include "QuadraticBezier.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "../../core/math/Geometry.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Window/Mouse.hpp"


ui::elements::LerpBezier::LerpBezier(std::vector<common::Point> &&startPoints_)
    : startPoints(std::move(startPoints_)) {
    // Initial state
    for (auto &point: startPoints) {
        sf::RectangleShape rect(sf::Vector2f(point.size.x, point.size.y));
        rect.setPosition({point.position.x, point.position.y});
        rect.setFillColor(sf::Color::White);
        controlPoints.push_back(std::make_unique<sf::RectangleShape>(rect));
    }
}

void ui::elements::LerpBezier::draw(sf::RenderWindow &target, sf::Vector2f origin) const {
    // Control points
    for (auto &controlPoint: controlPoints) {
        target.draw(*controlPoint);
    }

    // Rather than iterate a float up to 1.0f, instead define steps and compute the increment.
    // This will avoid rounding quirks.
    int steps = 10;
    for (int i = 0; i <= steps; ++i) {
        float t = static_cast<float>(i) / steps;

        // Midpoint, points 1 - 2
        sf::Vector2f midPointA = core::math::lerp(controlPoints[0]->getPosition(), controlPoints[1]->getPosition(), t);
        sf::RectangleShape rectMidPointA{sf::Vector2f(5, 5)};
        rectMidPointA.setPosition(midPointA);
        rectMidPointA.setFillColor(sf::Color::Green);
        target.draw(rectMidPointA);

        // Midpoint, points 2 - 3
        sf::Vector2f midPointB = core::math::lerp(controlPoints[1]->getPosition(), controlPoints[2]->getPosition(), t);
        sf::RectangleShape rectMidPointB{sf::Vector2f(5, 5)};
        rectMidPointB.setPosition(midPointB);
        rectMidPointB.setFillColor(sf::Color::Green);
        target.draw(rectMidPointB);

        // Draw a line between our midpoints by defining the line using two vertices
        sf::Vertex line[] = {
            sf::Vertex(midPointA, sf::Color::Cyan),
            sf::Vertex(midPointB, sf::Color::Cyan)
        };

        target.draw(line, 2, sf::PrimitiveType::Lines);
    }
}

void ui::elements::LerpBezier::update(sf::RenderWindow &target, sf::Vector2f origin) const {
    // Handle dragging
    if (isDragging && draggedShape) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(target);
        draggedShape->setPosition({mousePos.x - dragOffset.x, mousePos.y - dragOffset.y});
    }
}

void ui::elements::LerpBezier::handleMouseMove(sf::Vector2f &mousePos) {

}

void ui::elements::LerpBezier::handleMouseButtonPressed(sf::Vector2f &mousePos) {
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

void ui::elements::LerpBezier::handleMouseButtonReleased() {
    // Reset our bool and dragged shape
    isDragging = false;
    draggedShape = nullptr;
}
