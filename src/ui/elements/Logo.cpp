#include "Logo.hpp"

#include "SFML/Graphics/RectangleShape.hpp"
#include "../../core/math/Geometry.hpp"

ui::elements::Logo::Logo(
    common::Path &&path_
) : path(std::move(path_)) {
}

void ui::elements::Logo::draw(sf::RenderWindow &target, sf::Vector2f origin) const {
    // iterate path segments
    for (auto &segment: path.segments) {
        if (segment.type == common::SegmentType::LINE) {
            std::vector<sf::RectangleShape> shapes;
            for (auto &point: segment.points) {
                sf::RectangleShape rect(sf::Vector2f(point.size.x, point.size.y));
                rect.setPosition({point.position.x, point.position.y});
                rect.setFillColor(sf::Color::White);

                // point draw
                target.draw(*std::make_unique<sf::RectangleShape>(rect));
                shapes.push_back(rect);
            }

            // initialise an empty vertex and then iterate the shapes object to fill the vertex
            std::vector<sf::Vertex> line;
            for (size_t i = 0; i < shapes.size() - 1; i++) {
                line.push_back(sf::Vertex({shapes[i].getPosition(), sf::Color::White}));
                line.push_back(sf::Vertex({shapes[i + 1].getPosition(), sf::Color::White}));
            }

            target.draw(&line[0], 2, sf::PrimitiveType::Lines);
        }

        if (segment.type == common::SegmentType::CURVE) {

            sf::Vector2f midPos = (segment.points[0].position + segment.points[1].position) * 0.5f;
            common::Point midPoint = {"mid point", midPos, segment.points[0].size * 0.5f};
            std::vector points = {segment.points[0], midPoint, segment.points[1]};

            // Draw points
            std::vector<sf::RectangleShape> shapes;
            for (auto &point: points) {
                sf::RectangleShape rect(sf::Vector2f(point.size.x, point.size.y));
                rect.setPosition({point.position.x, point.position.y});
                rect.setFillColor(sf::Color::White);
                target.draw(*std::make_unique<sf::RectangleShape>(rect));
                shapes.push_back(rect);
            }

            // Draw quadratic curve
            std::vector<sf::Vertex> bezierLine;
            for (float t = 0; t <= 1.0f; t += 0.01f) {
                sf::Vector2f segmentVector = core::math::quadraticBezier(
                    shapes[0].getPosition(),
                    shapes[1].getPosition(),
                    shapes[2].getPosition(),
                    t
                );
                bezierLine.push_back(sf::Vertex({segmentVector, sf::Color::White}));
            }

            target.draw(&bezierLine[0], bezierLine.size(), sf::PrimitiveType::LineStrip);
        }
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
