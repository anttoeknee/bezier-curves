#pragma once
#include "Region.hpp"
#include "../elements/QuadraticBezier.hpp"

class Bezier : public Region {
    std::vector<PointData> startPoints{};

public:
    Bezier();

    void handleMouseButtonReleased() override;

    void handleMouseButtonPressed(sf::Vector2i &mousePos) override;

    void draw(sf::RenderWindow &target) const override;

    void update(sf::RenderWindow &target) const override;
};
