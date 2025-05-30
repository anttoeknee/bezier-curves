#pragma once
#include "SFML/Graphics/RenderWindow.hpp"

struct Element {
    virtual void draw(sf::RenderWindow &target) const = 0;

    virtual void update(sf::RenderWindow &target) const = 0;

    virtual void handleMouseButtonPressed(sf::Vector2i &mousePos) = 0;

    virtual void handleMouseButtonReleased() = 0;

    virtual ~Element() = default;
};
