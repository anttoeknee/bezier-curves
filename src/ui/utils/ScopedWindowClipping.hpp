#pragma once

#include <SFML/Graphics.hpp>

namespace ui::utils {
    class ScopedWindowClipping {
        sf::RenderWindow &target;
        sf::View oldView;

    public:
        ScopedWindowClipping(sf::RenderWindow &target,
                       const sf::Vector2f &position,
                       const sf::Vector2f &size)
            : target(target), oldView(target.getView()) {
            sf::View clipView(position + size * 0.5f, size);
            sf::Vector2f windowSize = static_cast<sf::Vector2f>(target.getSize());

            sf::FloatRect viewport({
                   position.x / windowSize.x,
                   position.y / windowSize.y
               }, {
                   size.x / windowSize.x,
                   size.y / windowSize.y
               });

            clipView.setViewport(viewport);
            target.setView(clipView);
        }

        ~ScopedWindowClipping() {
            target.setView(oldView);
        }
    };
}
