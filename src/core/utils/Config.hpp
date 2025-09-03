
#pragma once
#include <string>

namespace core::utils {
    struct Config {
        unsigned windowWidth;
        unsigned windowHeight;
        bool fullscreen;

        // Loads the config, with platform-specific details implemented elsewhere
        static Config load();
    };
}
