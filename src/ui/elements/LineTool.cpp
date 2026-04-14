#include <vector>

#include "Element.hpp"
#include "LineTool.hpp"

#include <iostream>

#include "../../core/mappers/SFMLMapper.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "../../core/math/Geometry.hpp"
#include "../common/Path.hpp"
#include "../rendering/Bezier.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Window/Mouse.hpp"

namespace ui::elements {
    void LineTool::draw(sf::RenderWindow &target, sf::Vector2f origin) {

        // Only draw the shapes we've actually created
        for (size_t i = 0; i < anchorPointCount; ++i) {
            target.draw(controlShapes[i]);
        }

        // Draw connecting line (what will be the curve)
        if (anchorPointCount == 2) {

            rendering::bezier::drawQuadraticCurve(
                target,
                controlShapes[0].getPosition(),
                controlShapes[2].getPosition(),
                controlShapes[1].getPosition()
            );

            // Create and draw the midpoint
            auto shape = rendering::bezier::createControlPoint(
                controlShapes.back().getPosition(),
                controlShapes.back().getSize(),
                sf::Color::Red
            );

            rendering::bezier::drawControlPoint(
                target,
                *shape
            );

            // Draw the midpoint to control point line (always anchored to first point)
            rendering::bezier::drawControlLine(
                target,
                controlShapes[0].getPosition(),
                controlShapes[2].getPosition(),
                sf::Color::Cyan
            );
        }
    }

    void LineTool::update(sf::RenderWindow &target, sf::Vector2f origin) {

        std::cout << "dragOffset: " << dragOffset.x << ", " << dragOffset.y << std::endl;

        // Handle dragging
        if (isDragging) {
            sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(target));
            controlShapes[draggedShapeIndex].setPosition(mousePos - dragOffset);
        }

        std::cout << "midPoint: " << midPoint.position.x << ", " << midPoint.position.y << std::endl;
    }

    void LineTool::handleMouseMove(sf::Vector2f &mousePos) {
    }


    void LineTool::handleMouseButtonPressed(const core::Vector2f &mousePos) {

        auto sfmlMousePos = core::mappers::SFMLMapper::toSfVector2f(mousePos);

        // First check if we're clicking on an existing anchor point for dragging
        for (size_t i = 0; i < anchorPointCount; ++i) {
            if (controlShapes[i].getGlobalBounds().contains(sfmlMousePos)) {
                isDragging = true;
                draggedShapeIndex = i;
                dragOffset = sfmlMousePos - controlShapes[i].getPosition();
                return;
            }
        }

        // Then check if we've clicked on the midpoint
        if (controlShapes.back().getGlobalBounds().contains(sfmlMousePos)) {
            draggedShapeIndex = 2;
            isDragging = true;
            dragOffset = sfmlMousePos - controlShapes.back().getPosition();
            return;
        }

        // Otherwise create a new anchorPoint if we haven't reached the limit
        if (anchorPointCount < 2) {

            std::cout << "Creating anchor point at: " << sfmlMousePos.x << ", " << sfmlMousePos.y << std::endl;
            std::cout << "anchorPointCount before: " << anchorPointCount << std::endl;

            common::Point anchorPoint = {"Point", sfmlMousePos, {15, 15}};

            // Write directly to the array at the next available index
            controlShapes[anchorPointCount].setSize(sf::Vector2f(anchorPoint.size.x, anchorPoint.size.y));
            controlShapes[anchorPointCount].setPosition({anchorPoint.position.x, anchorPoint.position.y});
            controlShapes[anchorPointCount].setFillColor(sf::Color::White);

            anchorPointCount++;  // Increment our counter

            std::cout << "anchorPointCount after: " << anchorPointCount << std::endl;
        }

        // If we have reached the limit then we define the midpoint
        if (anchorPointCount == 2) {
            sf::Vector2f midPos = (controlShapes[0].getPosition() + controlShapes[1].getPosition()) / 2.f;
            midPoint = {"Mid-point", midPos, controlShapes[0].getSize() * 0.5f};

            controlShapes[2].setSize(sf::Vector2f(midPoint.size.x, midPoint.size.y));
            controlShapes[2].setPosition({midPoint.position.x, midPoint.position.y});
            controlShapes[2].setFillColor(sf::Color::Red);
        }
    }

    void LineTool::handleMouseButtonReleased() {
        // Reset our bool and dragged shape
        isDragging = false;
    }
}
