
#pragma once

#include <SFML/System/Vector2.hpp>

namespace core::math {
    sf::Vector2f quadraticBezier(
        const sf::Vector2f& p0,
        const sf::Vector2f& p1,
        const sf::Vector2f& p2,
        float t
    );
}

