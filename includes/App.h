#ifndef APP_H
#define APP_H
#include "SFML/Graphics/RenderWindow.hpp"

#endif //APP_H

class App {
public:
    App();

    void run();

private:
    sf::RenderWindow window;

    void handleEvents();

    void update();

    void render();
};
