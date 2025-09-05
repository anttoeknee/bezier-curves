#pragma once
#include "Element.hpp"
#include "../common/Point.hpp"
#include "SFML/Graphics/Shape.hpp"

namespace ui::elements {

    class Logo : public Element {
        std::vector<std::unique_ptr<sf::Shape> > controlPoints;
        std::vector<common::Point> startPoints;

    public:
        explicit Logo(std::vector<common::Point> &&startPoints_);

        void draw(sf::RenderWindow &target, sf::Vector2f origin) const override;

        void update(sf::RenderWindow &target, sf::Vector2f origin) const override;

        void handleMouseMove(sf::Vector2f &mousePos) override;

        void handleMouseButtonPressed(sf::Vector2f &mousePos) override;

        void handleMouseButtonReleased() override;
    };
}
