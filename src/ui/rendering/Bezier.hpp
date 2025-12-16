#pragma once
#include "SFML/Graphics/RenderWindow.hpp"

namespace ui::rendering::bezier {
    void drawQuadraticCurve(
        sf::RenderWindow &target,
        const sf::Vector2f &start,
        const sf::Vector2f &control,
        const sf::Vector2f &end,
        const sf::Color &color = sf::Color::White,
        float step = 0.01f
    );

    void drawControlPoint(
        sf::RenderWindow &target,
        const sf::Vector2f &position,
        const sf::Vector2f &size,
        const sf::Color &color = sf::Color::Red
    );

    void drawControlLine(
        sf::RenderWindow &target,
        const sf::Vector2f &from,
        const sf::Vector2f &to,
        const sf::Color &color = sf::Color::Cyan
    );
}
