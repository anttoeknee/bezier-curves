#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "../../core/common/Vector2f.hpp"

namespace ui::elements {
    struct Element {

        virtual void draw(sf::RenderWindow &target, sf::Vector2f origin) = 0;

        virtual void update(sf::RenderWindow &target, sf::Vector2f origin) = 0;

        virtual void handleMouseMove(sf::Vector2f &mousePos) = 0;

        virtual void handleMouseButtonPressed(const core::Vector2f &mousePos) = 0;

        virtual void handleMouseButtonReleased() = 0;

        virtual ~Element() = default;
    };
}

