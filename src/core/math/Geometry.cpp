#include "Geometry.hpp"

sf::Vector2f core::math::quadraticBezier(
    const sf::Vector2f &p0,
    const sf::Vector2f &p1,
    const sf::Vector2f &p2,
    float t
) {
    float u = 1 - t;
    return u * u * p0 + 2 * u * t * p1 + t * t * p2;
}

sf::Vector2f core::math::lerp(const sf::Vector2f &a, const sf::Vector2f &b, float t) {
    return (1.0f - t) * a + t * b;
}
