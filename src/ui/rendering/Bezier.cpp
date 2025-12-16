#include "Bezier.hpp"
#include "../../core/math/Geometry.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

namespace ui::rendering::bezier {
    void drawQuadraticCurve(sf::RenderWindow &target, const sf::Vector2f &start, const sf::Vector2f &control,
                            const sf::Vector2f &end, const sf::Color &color, float step) {
        std::vector<sf::Vertex> bezierLine;
        for (float t = 0; t <= 1.0f; t += step) {
            sf::Vector2f point = core::math::quadraticBezier(start, control, end, t);
            bezierLine.push_back(sf::Vertex({point, color}));
        }

        // Apparently, SFML draws the rest of the vertices; we only need to say where to start from
        target.draw(&bezierLine[0], bezierLine.size(), sf::PrimitiveType::LineStrip);
    }

    void drawControlPoint(sf::RenderWindow &target, const sf::RectangleShape &controlPoint) {
        target.draw(controlPoint);
    }

    std::unique_ptr<sf::RectangleShape> createControlPoint(const sf::Vector2f &position, const sf::Vector2f &size,
        const sf::Color &color) {

        auto rect = std::make_unique<sf::RectangleShape>(size);

        rect->setPosition(position);
        rect->setFillColor(color);

        return rect;
    }

    void drawControlLine(sf::RenderWindow &target, const sf::Vector2f &from, const sf::Vector2f &to,
                         const sf::Color &color) {
        sf::Vertex line1[] = {
            sf::Vertex(from, color),
            sf::Vertex(to, color)
        };
        target.draw(line1, 2, sf::PrimitiveType::Lines);
    }
}
