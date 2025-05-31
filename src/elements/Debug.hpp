
#pragma once
#include "Element.hpp"

class Debug : public Element {
    public:
    void draw(sf::RenderWindow &target) const override;

    void update(sf::RenderWindow &target) const override;

    void handleMouseButtonPressed(sf::Vector2i &mousePos) override;

    void handleMouseButtonReleased() override;

    Debug();
};
