
#pragma once
#include "Point.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

namespace ui::common {
    struct ControlPoint {
        Point point;
        std::unique_ptr<sf::RectangleShape> shape;

        ControlPoint(Point point_, sf::Color color = sf::Color::Red)
            : point(std::move(point_)) {
            shape = std::make_unique<sf::RectangleShape>(point.size);
            shape->setPosition(point.position);
            shape->setFillColor(color);
        }

        // Update both at once
        void setPosition(sf::Vector2f newPos) {
            point.position = newPos;
            shape->setPosition(newPos);
        }

        sf::Vector2f getPosition() const {
            return point.position;
        }
    };
}
