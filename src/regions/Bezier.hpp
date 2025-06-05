#pragma once
#include "Region.hpp"
#include "../elements/QuadraticBezier.hpp"

class Bezier : public Region {
    std::vector<PointData> startPoints{};

public:
    explicit Bezier(sf::RenderWindow &target);

    ~Bezier() override;

    void handleMouseButtonReleased() override;

    void handleMouseButtonPressed(sf::Vector2f &mousePos) override;

    void draw() const override;

    void update() const override;
};
