#include "SFMLMapper.hpp"


namespace core::mappers::SFMLMapper {
    MouseButton toMouseButton(sf::Mouse::Button button) {
        switch (button) {
            case sf::Mouse::Button::Left: return core::MouseButton::Left;
            case sf::Mouse::Button::Right: return core::MouseButton::Right;
            case sf::Mouse::Button::Middle: return core::MouseButton::Middle;
            default: return core::MouseButton::Left;
        }
    }

    Vector2f toVector2f(sf::Vector2f v) {
        return Vector2f{v.x, v.y};
    }

    sf::Vector2f toSfVector2f(Vector2f v) {
        return {v.x, v.y};
    }
}


