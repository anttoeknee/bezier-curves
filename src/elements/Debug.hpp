#pragma once
#include "Element.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

class Debug : public Element {
    sf::Font font;
    mutable sf::Text text;

public:
    void draw(sf::RenderWindow &target) const override;

    void update(sf::RenderWindow &target) const override;

    void handleMouseButtonPressed(sf::Vector2i &mousePos) override;

    void handleMouseButtonReleased() override;

    Debug();
};
