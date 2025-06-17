#pragma once
#include "Region.hpp"
#include "../elements/QuadraticBezier.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

namespace ui::regions {
    class Debug : public Region {
        mutable sf::RectangleShape container;
    public:
        Debug(sf::RenderWindow &target, std::vector<std::unique_ptr<elements::Element> > &&elements, sf::Vector2f position, sf::Vector2f size);

        void handleMouseMove(sf::Vector2f &mousePos) override;

        void handleMouseButtonReleased() override;

        void handleMouseButtonPressed(sf::Vector2f &mousePos) override;

        void draw() const override;

        void update() const override;
    };
}

