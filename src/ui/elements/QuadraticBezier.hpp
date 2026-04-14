#pragma once
#include "Element.hpp"
#include "../../core/common/Vector2f.hpp"
#include "../../core/utils/AssetManager.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "../common/Point.hpp"

namespace ui::elements {

    class QuadraticBezier : public Element {
        std::vector<std::unique_ptr<sf::Shape> > controlPoints;
        std::vector<common::Point> startPoints;

        bool isDragging = false;
        sf::Shape *draggedShape = nullptr;
        sf::Vector2f dragOffset;

    public:
        explicit QuadraticBezier(std::vector<common::Point> &&startPoints);

        void draw(sf::RenderWindow &target, sf::Vector2f origin) override;

        void update(sf::RenderWindow &target, sf::Vector2f origin) override;

        void handleMouseMove(sf::Vector2f &mousePos) override;

        void handleMouseButtonPressed(const core::Vector2f &mousePos) override;

        void handleMouseButtonReleased() override;
    };
}
