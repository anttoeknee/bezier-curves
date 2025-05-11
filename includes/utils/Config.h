
#pragma once
#include <string>

struct Config {
    unsigned windowWidth;
    unsigned windowHeight;
    bool fullscreen;
    std::string fontPath;

    // Loads the config, with platform-specific details implemented elsewhere
    static Config load();
};
