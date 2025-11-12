
#pragma once

#include "Element.hpp"
#include "../common/Path.hpp"
#include "SFML/Graphics/Shape.hpp"

namespace ui::elements {
    class LineTool : public Element {
        std::vector<common::Point> startPoints;
        std::vector<std::unique_ptr<sf::Shape> > anchorPoints;

        // TODO: move into a shared object
        bool isDragging = false;
        sf::Shape *draggedShape = nullptr;
        sf::Vector2f dragOffset;
    public:
        void draw(sf::RenderWindow &target, sf::Vector2f origin) const override;

        void update(sf::RenderWindow &target, sf::Vector2f origin) const override;

        void handleMouseMove(sf::Vector2f &mousePos) override;

        void handleMouseButtonPressed(sf::Vector2f &mousePos) override;

        void handleMouseButtonReleased() override;

        LineTool(std::vector<common::Point> &&startPoints);
    };
}
