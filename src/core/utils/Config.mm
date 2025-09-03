
#include "Config.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

core::utils::Config core::utils::Config::load() {

    try {
        std::ifstream f("config.json");
        if (!f.is_open()) {
            throw std::runtime_error("Could not open config.json");
        }
        json data = json::parse(f);

        return {
            data.value("window.width", 1280u),
            data.value("window.height", 810u),
            data.value("window.fullscreen", false),
            data.value("window.vsync", true),
            data.value("window.title", "Application"),
        };
    } catch (const std::exception& e) {
        std::cerr << "Config error: " << e.what() << ", using defaults\n";
        // Return default values on error
        return {1280u, 810u, false, true, "Application"};
    }
}


