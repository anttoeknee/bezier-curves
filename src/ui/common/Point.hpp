
#pragma once
#include <string>

#include "SFML/System/Vector2.hpp"

namespace ui::common {
    struct Point {
        std::string name;
        sf::Vector2f position;
        sf::Vector2f size;
    };
}

