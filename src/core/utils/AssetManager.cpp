
#include "./AssetManager.hpp"
#include "SFML/Graphics/Font.hpp"

sf::Font core::utils::AssetManager::loadEmbeddedFont() {
    sf::Font font;
    size_t size = _binary_segoeui_ttf_end - _binary_segoeui_ttf_start;

    if (!font.openFromMemory(_binary_segoeui_ttf_start, size)) {
        throw std::runtime_error("Failed to load font!");
    }

    return font;
}