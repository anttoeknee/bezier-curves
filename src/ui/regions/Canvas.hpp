#pragma once
#include "Region.hpp"
#include "../elements/QuadraticBezier.hpp"

namespace ui::regions {
    class Canvas : public Region {
        std::vector<common::Point> startPoints{};

    public:
        explicit Canvas(sf::RenderWindow &target, sf::Vector2f position, sf::Vector2f size);

        ~Canvas() override;

        void handleMouseMove(sf::Vector2f &mousePos) override;

        void handleMouseButtonReleased() override;

        void handleMouseButtonPressed(sf::Vector2f &mousePos) override;

        void draw() const override;

        void update() const override;
    };
}

