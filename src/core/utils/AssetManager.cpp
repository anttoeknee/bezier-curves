#include "./AssetManager.hpp"
#include "SFML/Graphics/Font.hpp"

sf::Font core::utils::AssetManager::loadEmbeddedFont() {
    sf::Font font;

#if defined(__APPLE__) || defined(_WIN32)
    const auto* start = _binary_segoeui_ttf_start;
    const auto* end = _binary_segoeui_ttf_end;
#else
    const auto* start = _binary_Ubuntu_ttf_start;
    const auto* end = _binary_Ubuntu_ttf_end;
#endif

    size_t size = end - start;
    if (!font.openFromMemory(start, size)) {
        throw std::runtime_error("Failed to load font!");
    }
    return font;
}