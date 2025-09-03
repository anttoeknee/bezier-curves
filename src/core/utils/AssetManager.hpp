
#pragma once
#include "SFML/Graphics/Font.hpp"

extern "C" {
    extern const char _binary_segoeui_ttf_start[];
    extern const char _binary_segoeui_ttf_end[];
}

namespace core::utils {
    class AssetManager {
    public:
        static sf::Font loadEmbeddedFont();
    };
}