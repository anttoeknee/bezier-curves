
#pragma once
#include <string>

namespace core::utils {
    struct Config {
        unsigned windowWidth;
        unsigned windowHeight;
        bool fullscreen;
        bool vsync;
        std::string title;

        // Loads the config, with platform-specific details implemented elsewhere
        static Config load();
    };
}
