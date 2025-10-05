

#include <vector>

#include "Element.hpp"
#include "LineTool.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "../../core/math/Geometry.hpp"
#include "../common/Path.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Window/Mouse.hpp"


ui::elements::LineTool::LineTool(std::vector<common::Point> &&startPoints_)
    : startPoints(std::move(startPoints_)) {

    // Initial state
    // for (auto &point: startPoints) {
    //     sf::RectangleShape rect(sf::Vector2f(point.size.x, point.size.y));
    //     rect.setPosition({point.position.x, point.position.y});
    //     rect.setFillColor(sf::Color::White);
    //     anchorPoints.push_back(std::make_unique<sf::RectangleShape>(rect));
    // }
}

void ui::elements::LineTool::draw(sf::RenderWindow &target, sf::Vector2f origin) const {
    // Anchor points
    for (auto &anchorPoint: anchorPoints) {
        target.draw(*anchorPoint);
    }

    // Compute control points
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

    std::vector midPointCtrlPointCandidates = { mpCandidate1, mpCandidate2 };


    std::vector points = {startPoints[0], startPoints[1]};

    // Draw points
    std::vector<sf::RectangleShape> shapes;
    for (auto &point: points) {
        sf::RectangleShape rect(sf::Vector2f(point.size.x, point.size.y));
        rect.setPosition({point.position.x, point.position.y});
        rect.setFillColor(sf::Color::White);
        target.draw(*std::make_unique<sf::RectangleShape>(rect));
        shapes.push_back(rect);
    }

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

    //target.draw(&bezierLine[0], bezierLine.size(), sf::PrimitiveType::LineStrip);
}

void ui::elements::LineTool::update(sf::RenderWindow &target, sf::Vector2f origin) const {

}

void ui::elements::LineTool::handleMouseMove(sf::Vector2f &mousePos) {

}


void ui::elements::LineTool::handleMouseButtonPressed(sf::Vector2f &mousePos) {

}

void ui::elements::LineTool::handleMouseButtonReleased() {

}
