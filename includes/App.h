#ifndef APP_H
#define APP_H

#include "Point.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "utils/Config.h"

#endif //APP_H

class App {
public:

    Config config;

    std::string title;

    App(Config config);

    void run();

private:
    sf::RenderWindow window;

    std::vector<std::unique_ptr<sf::Shape>> shapes;

    void handleEvents();

    void update();

    void render();
};
