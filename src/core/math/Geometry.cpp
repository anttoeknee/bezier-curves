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

sf::Vector2f cubicBezier(
    const sf::Vector2f& p0,
    const sf::Vector2f& p1,
    const sf::Vector2f& p2,
    const sf::Vector2f& p3,
    float t)
{
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    sf::Vector2f result =
        uuu * p0 +                // (1-t)^3 * P0
        3 * uu * t * p1 +         // 3(1-t)^2 * t * P1
        3 * u * tt * p2 +         // 3(1-t) * t^2 * P2
        ttt * p3;                 // t^3 * P3

    return result;
}

sf::Vector2f core::math::lerp(const sf::Vector2f &a, const sf::Vector2f &b, float t) {
    return (1.0f - t) * a + t * b;
}
