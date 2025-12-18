#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "core/utils/Config.hpp"
#include "ui/regions/Region.hpp"

class App {
public:
    core::utils::Config config;

    std::string title;

    App(core::utils::Config config);

    void run();

private:
    sf::RenderWindow window;

    const std::string APP_REGION_PEN_TOOL = "Primitive Pen Tool";

    void handleEvents();

    void update();

    void render();

    std::vector<std::unique_ptr<ui::regions::Region>> regions;
};
