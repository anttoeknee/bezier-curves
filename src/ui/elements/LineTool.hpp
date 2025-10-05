
#pragma once

#include "Element.hpp"
#include "../common/Path.hpp"
#include "SFML/Graphics/Shape.hpp"

namespace ui::elements {
    class LineTool : public Element {
        std::vector<common::Point> startPoints;
        std::vector<std::unique_ptr<sf::Shape> > anchorPoints;
    public:
        void draw(sf::RenderWindow &target, sf::Vector2f origin) const override;

        void update(sf::RenderWindow &target, sf::Vector2f origin) const override;

        void handleMouseMove(sf::Vector2f &mousePos) override;

        void handleMouseButtonPressed(sf::Vector2f &mousePos) override;

        void handleMouseButtonReleased() override;

        LineTool(std::vector<common::Point> &&startPoints);
    };
}
