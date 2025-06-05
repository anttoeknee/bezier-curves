#pragma once
#include "Region.hpp"
#include "../elements/QuadraticBezier.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class Debug : public Region {
    mutable sf::RectangleShape container;
public:
    Debug();

    void handleMouseButtonReleased() override;

    void handleMouseButtonPressed(sf::Vector2i &mousePos) override;

    void draw(sf::RenderWindow &target) const override;

    void update(sf::RenderWindow &target) const override;
};
