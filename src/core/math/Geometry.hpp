#pragma once

#include <SFML/System/Vector2.hpp>

namespace core::math {
    sf::Vector2f quadraticBezier(
        const sf::Vector2f &p0,
        const sf::Vector2f &p1,
        const sf::Vector2f &p2,
        float t
    );

    sf::Vector2f cubicBezier(
        const sf::Vector2f &p0,
        const sf::Vector2f &p1,
        const sf::Vector2f &p2,
        const sf::Vector2f &p3,
        float t
    );

    sf::Vector2f lerp(const sf::Vector2f &a, const sf::Vector2f &b, float t);
}
