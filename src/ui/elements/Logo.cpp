#include "Logo.hpp"

#include "SFML/Graphics/RectangleShape.hpp"
#include "../rendering/Bezier.hpp"
#include "../common/ControlPoint.hpp"

ui::elements::Logo::Logo(
    common::Path &&path_
) : path(std::move(path_)) {

}

void ui::elements::Logo::draw(sf::RenderWindow &target, sf::Vector2f origin) {
    size_t cpIndex = 0;

    for (auto &segment: path.segments) {
        if (segment.type == common::SegmentType::LINE) {
            rendering::bezier::drawControlLine(
                target,
                segment.points[0].position,
                segment.points[1].position,
                sf::Color::White
            );
            for (auto &point: segment.points) {
                auto shape = rendering::bezier::createControlPoint(
                    point.position, point.size, sf::Color::White
                );
                rendering::bezier::drawControlPoint(target, *shape);
            }
        }

        if (segment.type == common::SegmentType::CURVE) {

            rendering::bezier::drawQuadraticCurve(
                target,
                segment.points[0].position,
                controlPoints[cpIndex].getPosition(),
                segment.points[1].position
            );

            rendering::bezier::drawControlLine(
                target,
                segment.points[0].position,
                controlPoints[cpIndex].getPosition(),
                sf::Color::Cyan
            );

            cpIndex++;
        }
    }

    // Draw control point shapes
    for (auto &cp : controlPoints) {
        target.draw(*cp.shape);
    }

}

void ui::elements::Logo::update(sf::RenderWindow &target, sf::Vector2f origin) {
    if (!shapesInitialized) {
        for (auto &segment: path.segments) {
            if (segment.type == common::SegmentType::CURVE) {
                // Compute midpoint (with a very small offset to bring out the curve slightly)
                sf::Vector2f midPos = (segment.points[0].position + segment.points[1].position) * 0.5f;
                midPos *= 0.98f;

                common::Point midPoint{"Midpoint", midPos, segment.points[0].size};
                segment.points.push_back(midPoint);

                // Create control point with both data and shape
                controlPoints.emplace_back(midPoint, sf::Color::Red);
            }
        }
        shapesInitialized = true;
    }

    // Handle dragging
    if (isDragging && draggedControlPoint) {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(target));
        draggedControlPoint->setPosition(mousePos - dragOffset);
    }
}

void ui::elements::Logo::handleMouseMove(sf::Vector2f &mousePos) {
}

void ui::elements::Logo::handleMouseButtonPressed(sf::Vector2f &mousePos) {
    for (auto &cp : controlPoints) {
        if (cp.shape->getGlobalBounds().contains(mousePos)) {
            draggedControlPoint = &cp;
            isDragging = true;
            dragOffset = mousePos - cp.getPosition();
            return;
        }
    }
}

void ui::elements::Logo::handleMouseButtonReleased() {
    isDragging = false;
}
