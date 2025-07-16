#pragma once
#include "Element.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "../common/Point.hpp"

namespace ui::elements {

    class QuadraticBezier : public Element {
        std::vector<std::shared_ptr<sf::Shape> > controlPoints;
        std::vector<common::Point> startPoints;

        bool isDragging = false;
        sf::Shape *draggedShape = nullptr;
        sf::Vector2f dragOffset;

    public:
        explicit QuadraticBezier(const std::vector<common::Point>& startPoints);

        void draw(sf::RenderWindow &target, sf::Vector2f origin) const override;

        void update(sf::RenderWindow &target, sf::Vector2f origin) const override;

        void handleMouseMove(sf::Vector2f &mousePos) override;

        void handleMouseButtonPressed(sf::Vector2f &mousePos) override;

        void handleMouseButtonReleased() override;
    };
}
