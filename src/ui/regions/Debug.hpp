#pragma once
#include "Region.hpp"
#include "../elements/QuadraticBezier.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class Debug : public Region {
    mutable sf::RectangleShape container;
public:
    explicit Debug(sf::RenderWindow &target);

    void handleMouseButtonReleased() override;

    void handleMouseButtonPressed(sf::Vector2f &mousePos) override;

    void draw() const override;

    void update() const override;
};
