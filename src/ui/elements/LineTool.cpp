#include <vector>

#include "Element.hpp"
#include "LineTool.hpp"

#include <iostream>

#include "SFML/Graphics/Vertex.hpp"
#include "../../core/math/Geometry.hpp"
#include "../common/Path.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Window/Mouse.hpp"

namespace ui::elements {
    void LineTool::draw(sf::RenderWindow &target, sf::Vector2f origin) const {

        std::cout << "Drawing " << anchorPointCount << " anchor points" << std::endl;

        for (size_t i = 0; i < anchorPointCount; ++i) {
            std::cout << "  Point " << i << " at: "
                      << anchorShapes[i].getPosition().x << ", "
                      << anchorShapes[i].getPosition().y << std::endl;
            target.draw(anchorShapes[i]);
        }

        // Only draw the shapes we've actually created
        for (size_t i = 0; i < anchorPointCount; ++i) {
            target.draw(anchorShapes[i]);
        }

        /* Compute control points
        sf::Vector2f midPos = (startPoints[0].position + startPoints[1].position) * 0.5f;
        common::Point midPoint = {"mid point", midPos, startPoints[0].size * 0.2f};

        // calculate outbound and inbound control point candidates
        common::Point mpCandidate1 = {
            "cp candidate 1",
            {
                midPoint.position.x * 0.9f,
                midPoint.position.y * 0.9f
            },
            {10, 10}
        };

        common::Point mpCandidate2 = {
            "cp candidate 2",
            {
                midPoint.position.x * 1.1f,
                midPoint.position.y * 1.1f
            },
            {10, 10}
        };

        std::vector midPointCtrlPointCandidates = {mpCandidate1, mpCandidate2};


        //std::vector points = {startPoints[0], startPoints[1]};

        // Draw points
        std::vector<sf::RectangleShape> shapes;
        // for (auto &point: points) {
        //     sf::RectangleShape rect(sf::Vector2f(point.size.x, point.size.y));
        //     rect.setPosition({point.position.x, point.position.y});
        //     rect.setFillColor(sf::Color::White);
        //     target.draw(*std::make_unique<sf::RectangleShape>(rect));
        //     shapes.push_back(rect);
        // }

        // Draw midpoint to stand out
        sf::RectangleShape rect(sf::Vector2f(midPoint.size.x, midPoint.size.y));
        rect.setPosition({midPoint.position.x, midPoint.position.y});
        rect.setFillColor(sf::Color::Red);
        target.draw(*std::make_unique<sf::RectangleShape>(rect));
        shapes.push_back(rect);

        // Draw control point candidates
        std::vector<sf::RectangleShape> midPointShapes;
        for (auto &cpCandidate: midPointCtrlPointCandidates) {
            sf::RectangleShape rect(sf::Vector2f(cpCandidate.size.x, cpCandidate.size.y));
            rect.setPosition({cpCandidate.position.x, cpCandidate.position.y});
            rect.setFillColor(sf::Color::Cyan);
            target.draw(*std::make_unique<sf::RectangleShape>(rect));
            midPointShapes.push_back(rect);
        }

        // Draw connecting line between control point candidates and mid point
        std::vector<sf::Vertex> ctrlPointLines;
        for (auto &cpCandidate: midPointShapes) {
            //ctrlPointLines.push_back(sf::Vertex({midPointShapes[0].getPosition(), sf::Color::Cyan}));
            //ctrlPointLines.push_back(sf::Vertex({cpCandidate.getPosition(), sf::Color::Cyan}));
        }

        //target.draw(&bezierLine[0], bezierLine.size(), sf::PrimitiveType::LineStrip);*/
    }

    void LineTool::update(sf::RenderWindow &target, sf::Vector2f origin) {

        std::cout << "dragOffset: " << dragOffset.x << ", " << dragOffset.y << std::endl;

        // Handle dragging
        if (isDragging) {
            sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(target));
            anchorShapes[draggedShapeIndex].setPosition(mousePos - dragOffset);
        }
    }

    void LineTool::handleMouseMove(sf::Vector2f &mousePos) {
    }


    void LineTool::handleMouseButtonPressed(sf::Vector2f &mousePos) {
        // First check if we're clicking on an existing anchor point for dragging
        for (size_t i = 0; i < anchorPointCount; ++i) {
            if (anchorShapes[i].getGlobalBounds().contains(mousePos)) {
                isDragging = true;
                draggedShapeIndex = i;
                dragOffset = mousePos - anchorShapes[i].getPosition();
                return;
            }
        }

        // Otherwise create a new anchorPoint if we haven't reached the limit
        if (anchorPointCount < 2) {

            std::cout << "Creating anchor point at: " << mousePos.x << ", " << mousePos.y << std::endl;
            std::cout << "anchorPointCount before: " << anchorPointCount << std::endl;

            common::Point anchorPoint = {"Point", mousePos, {15, 15}};

            // Write directly to the array at the next available index
            anchorShapes[anchorPointCount].setSize(sf::Vector2f(anchorPoint.size.x, anchorPoint.size.y));
            anchorShapes[anchorPointCount].setPosition({anchorPoint.position.x, anchorPoint.position.y});
            anchorShapes[anchorPointCount].setFillColor(sf::Color::White);

            anchorPointCount++;  // Increment our counter

            std::cout << "anchorPointCount after: " << anchorPointCount << std::endl;
        }
    }

    void LineTool::handleMouseButtonReleased() {
        // Reset our bool and dragged shape
        isDragging = false;
        draggedShape = nullptr;
    }
}
