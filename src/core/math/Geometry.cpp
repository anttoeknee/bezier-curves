#include "Geometry.hpp"

sf::Vector2f math::quadraticBezier(
    const sf::Vector2f &p0,
    const sf::Vector2f &p1,
    const sf::Vector2f &p2,
    float t
) {
    float u = 1 - t;
    return u * u * p0 + 2 * u * t * p1 + t * t * p2;
}
