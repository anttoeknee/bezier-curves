#pragma once

#include <SFML/Graphics.hpp>

namespace ui::utils {
    /**
     * @brief Scoped guard that clips a render window to a centered view.
     *
     * Constructs a view centered on the given position and size, applies it to the target
     * render window, and restores the original view upon destruction. This ensures that
     * rendering operations are clipped to the specified region for the lifetime of the object.
     *
     * Usage of this class follows the RAII principle.
     *
     * @note This is intended to be used inside a draw loop!
     */
    class ScopedWindowClipping {
        sf::RenderWindow &target;
        sf::View oldView;

    public:
        /**
         * @brief Constructs and applies a clipped view to the given render window.
         *
         * @param target The render window to apply the clipping view to.
         * @param position The top-left corner of the clipping region.
         * @param size The size of the clipping region.
         */
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

        /// @brief Restores the original view to the render window.
        ~ScopedWindowClipping() {
            target.setView(oldView);
        }
    };
}
