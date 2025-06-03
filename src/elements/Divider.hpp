#pragma once
#include "Element.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Divider : public Element {
    mutable sf::RectangleShape line;
public:
    void draw(sf::RenderWindow &target) const override;

    void update(sf::RenderWindow &target) const override;

    void handleMouseButtonPressed(sf::Vector2i &mousePos) override;

    void handleMouseButtonReleased() override;

    Divider();
};
