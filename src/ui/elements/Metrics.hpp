#pragma once
#include "Element.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

namespace ui::elements {
    class Metrics : public Element {
        mutable sf::RectangleShape container;
        sf::Font font;
        mutable sf::Text memText;
        mutable sf::Text mousePosText;

    public:
        void draw(sf::RenderWindow &target, sf::Vector2f origin) const override;

        void update(sf::RenderWindow &target, sf::Vector2f origin) override;

        void memoryUsage(sf::Vector2f origin) const;

        void mousePosition(sf::Vector2f origin) const;

        void handleMouseMove(sf::Vector2f &mousePos) override;

        void handleMouseButtonPressed(sf::Vector2f &mousePos) override;

        void handleMouseButtonReleased() override;

        Metrics();
    };
}

