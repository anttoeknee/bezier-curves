#pragma once
#include "../common/MouseButton.hpp"
#include "../common/Vector2f.hpp"
#include "SFML/Window/Mouse.hpp"

namespace core::mappers::SFMLMapper {
    MouseButton toMouseButton(sf::Mouse::Button button);
    Vector2f toVector2f(sf::Vector2f v);
    sf::Vector2f toSfVector2f(Vector2f v);
}
