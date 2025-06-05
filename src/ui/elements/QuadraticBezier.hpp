#pragma once
#include "Element.hpp"
#include "SFML/Graphics/Shape.hpp"

namespace ui::elements {
    struct PointData {
        std::string name;
        sf::Vector2f position;
        sf::Vector2f size;
    };

    class QuadraticBezier : public Element {
        std::vector<std::unique_ptr<sf::Shape> > controlPoints;
        std::vector<PointData> startPoints;

        bool isDragging = false;
        sf::Shape *draggedShape = nullptr;
        sf::Vector2f dragOffset;

    public:
        explicit QuadraticBezier(std::vector<PointData> &&startPoints);

        void draw(sf::RenderWindow &target, sf::Vector2f origin) const override;

        void update(sf::RenderWindow &target, sf::Vector2f origin) const override;

        void handleMouseMove(sf::Vector2f &mousePos) override;

        void handleMouseButtonPressed(sf::Vector2f &mousePos) override;

        void handleMouseButtonReleased() override;
    };
}

