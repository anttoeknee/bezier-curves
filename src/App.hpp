#ifndef APP_H
#define APP_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "core/utils/Config.hpp"
#include "ui/regions/Region.hpp"

#endif //APP_H

class App {
public:
    core::utils::Config config;

    std::string title;

    App(core::utils::Config config);

    void run();

private:
    sf::RenderWindow window;

    void handleEvents();

    void update();

    void render();

    std::vector<std::unique_ptr<ui::regions::Region>> regions;
};
