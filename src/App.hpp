#pragma once

#include "core/events/EventBus.hpp"
#include "core/listeners/IListener.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "core/utils/Config.hpp"
#include "ui/regions/Region.hpp"

class App {
public:

    core::utils::Config config;

    std::string title;

    core::events::EventBus bus;

    App(core::utils::Config config);

    void run();

private:

    std::vector<std::unique_ptr<core::listeners::IListener>> listeners;

    sf::RenderWindow window;

    void bindEvents();

    void handleEvents();

    void update();

    void render();

    std::vector<std::unique_ptr<ui::regions::Region>> regions;
};
