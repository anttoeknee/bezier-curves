#pragma once
#include "Region.hpp"
#include "../elements/QuadraticBezier.hpp"

namespace ui::regions {
    class Bezier : public Region {
        std::vector<elements::PointData> startPoints{};

    public:
        explicit Bezier(sf::RenderWindow &target);

        ~Bezier() override;

        void handleMouseButtonReleased() override;

        void handleMouseButtonPressed(sf::Vector2f &mousePos) override;

        void draw() const override;

        void update() const override;
    };
}

