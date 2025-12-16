#include "Logo.hpp"

#include "SFML/Graphics/RectangleShape.hpp"
#include "../rendering/Bezier.hpp"

ui::elements::Logo::Logo(
    common::Path &&path_
) : path(std::move(path_)) {
}

void ui::elements::Logo::draw(sf::RenderWindow &target, sf::Vector2f origin) {
    // iterate path segments
    for (auto &segment: path.segments) {
        if (segment.type == common::SegmentType::LINE) {
            rendering::bezier::drawControlLine(
                target,
                segment.points[0].position,
                segment.points[1].position,
                sf::Color::White
            );
            for (auto &point: segment.points) {
                rendering::bezier::drawControlPoint(
                    target,
                    point.position,
                    point.size,
                    sf::Color::White
                );
            }
        }

        if (segment.type == common::SegmentType::CURVE) {
            rendering::bezier::drawQuadraticCurve(
                target,
                segment.points[0].position,
                segment.points[2].position,
                segment.points[1].position
            );

            // Draw the midpoint
            rendering::bezier::drawControlPoint(
                target,
                segment.points[2].position,
                segment.points[2].size
            );

            // Draw the midpoint to control point line (always anchored to first point)
            rendering::bezier::drawControlLine(
                target,
                segment.points[0].position,
                segment.points[2].position,
                sf::Color::Cyan
            );
        }
    }
}

void ui::elements::Logo::update(sf::RenderWindow &target, sf::Vector2f origin) {
    for (auto &segment: path.segments) {
        if (segment.type == common::SegmentType::CURVE) {
            // Compute midpoint (with a very small offset to bring out the curve slightly)
            sf::Vector2f midPos = (segment.points[0].position + segment.points[1].position) * 0.5f;
            midPos *= 0.98f;
            segment.points.push_back({"mid point", midPos, segment.points[0].size * 0.8f});
        }
    }
}

void ui::elements::Logo::handleMouseMove(sf::Vector2f &mousePos) {
}

void ui::elements::Logo::handleMouseButtonPressed(sf::Vector2f &mousePos) {
}

void ui::elements::Logo::handleMouseButtonReleased() {
}
