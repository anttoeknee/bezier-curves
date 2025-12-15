
#pragma once

#include "Element.hpp"
#include "../common/Path.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Shape.hpp"

namespace ui::elements {
    class LineTool : public Element {

        std::array<sf::RectangleShape, 2> anchorShapes;
        size_t anchorPointCount = 0;  // Track how many points we've created (0-2)

        // TODO: move into a shared object
        bool isDragging = false;
        size_t draggedShapeIndex = 0;  // Which shape is being dragged (0 or 1)
        sf::Shape *draggedShape = nullptr;
        sf::Vector2f dragOffset;
    public:
        void draw(sf::RenderWindow &target, sf::Vector2f origin) const override;

        void update(sf::RenderWindow &target, sf::Vector2f origin) override;

        void handleMouseMove(sf::Vector2f &mousePos) override;

        void handleMouseButtonPressed(sf::Vector2f &mousePos) override;

        void handleMouseButtonReleased() override;
    };
}
