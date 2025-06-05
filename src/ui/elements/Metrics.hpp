#pragma once
#include "Element.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

class Metrics : public Element {
    mutable sf::RectangleShape container;
    sf::Font font;
    mutable sf::Text text;

public:
    void draw(sf::RenderWindow &target, sf::Vector2f origin) const override;

    void update(sf::RenderWindow &target, sf::Vector2f origin) const override;

    void handleMouseButtonPressed(sf::Vector2f &mousePos) override;

    void handleMouseButtonReleased() override;

    Metrics();
};
