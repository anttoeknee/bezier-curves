#pragma once
#include "Element.hpp"
#include "../../core/common/Vector2f.hpp"
#include "../../core/utils/AssetManager.hpp"
#include "../common/Path.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "../common/ControlPoint.hpp"

namespace ui::common {
    struct ControlPoint;
}

namespace ui::elements {

    class Logo : public Element {
        common::Path path;

        std::vector<common::ControlPoint> controlPoints;
        common::ControlPoint* draggedControlPoint = nullptr;

        bool isDragging = false;
        sf::Vector2f dragOffset;
        bool shapesInitialized = false;

    public:
        explicit Logo(
            common::Path &&path_
        );

        void draw(sf::RenderWindow &target, sf::Vector2f origin) override;

        void update(sf::RenderWindow &target, sf::Vector2f origin) override;

        void handleMouseMove(sf::Vector2f &mousePos) override;

        void handleMouseButtonPressed(const core::Vector2f &mousePos) override;

        void handleMouseButtonReleased() override;
    };
}
