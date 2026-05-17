#pragma once
#include "SFML/Graphics/Font.hpp"

extern "C" {
#if defined(__APPLE__) || defined(_WIN32)
extern const char _binary_segoeui_ttf_start[];
extern const char _binary_segoeui_ttf_end[];
#else
extern const char _binary_Ubuntu_ttf_start[];
extern const char _binary_Ubuntu_ttf_end[];
#endif
}

namespace core::utils {
    class AssetManager {
    public:
        static sf::Font loadEmbeddedFont();
    };
}