#ifndef APP_H
#define APP_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "utils/Config.h"

#endif //APP_H

struct PointData {
    std::string name;
    sf::Vector2f position;
    sf::Vector2f size;
};

class App {
public:
    Config config;

    std::string title;

    App(Config config);

    void run();

    std::vector<PointData> startPoints;

private:
    sf::RenderWindow window;

    void handleEvents();

    void update();

    void render();

    sf::Vector2f quadraticBezier(
        const sf::Vector2f &p0,
        const sf::Vector2f &p1,
        const sf::Vector2f &p2,
        float t
    );

    std::vector<std::unique_ptr<sf::Shape>> shapes;

    bool isDragging = false;
    sf::Shape *draggedShape = nullptr;
    sf::Vector2f dragOffset;
};
