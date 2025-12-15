#pragma once
#include "Element.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

namespace ui::elements {
    class Divider : public Element {
        mutable sf::RectangleShape line;
    public:
        void draw(sf::RenderWindow &target, sf::Vector2f origin) const override;

        void update(sf::RenderWindow &target, sf::Vector2f origin) override;

        void handleMouseMove(sf::Vector2f &mousePos) override;

        void handleMouseButtonPressed(sf::Vector2f &mousePos) override;

        void handleMouseButtonReleased() override;

        Divider();
    };
}
