#ifndef APP_H
#define APP_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "core/utils/Config.hpp"
#include "elements/Element.hpp"

#endif //APP_H

class App {
public:
    Config config;

    std::string title;

    App(Config config);

    void run();

private:
    sf::RenderWindow window;

    void handleEvents();

    void update();

    void render();

    std::vector<std::unique_ptr<Element>> elements;
};
