#pragma once
#include "Element.hpp"
#include "../common/Path.hpp"
#include "../common/Point.hpp"
#include "SFML/Graphics/Shape.hpp"

namespace ui::elements {

    class Logo : public Element {
        common::Path path;

    public:
        explicit Logo(
            common::Path &&path_
        );

        void draw(sf::RenderWindow &target, sf::Vector2f origin) override;

        void update(sf::RenderWindow &target, sf::Vector2f origin) override;

        void handleMouseMove(sf::Vector2f &mousePos) override;

        void handleMouseButtonPressed(sf::Vector2f &mousePos) override;

        void handleMouseButtonReleased() override;
    };
}
