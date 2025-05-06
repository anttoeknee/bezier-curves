
#include <SFML/Graphics/Rect.hpp>

#include "../includes/App.h"
#include "SFML/Graphics/RectangleShape.hpp"


App::App()
    : window(sf::VideoMode({1920u, 1080u}), "Bezier Curves")
{
    window.setFramerateLimit(60);
}

void App::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void App::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void App::render() {
    window.clear();

    for (auto& shape : shapes) {
        window.draw(*shape);
    }

    window.display();
}

void App::update() {

    // Initial state for points
    // TODO: move point data somewhere else
    Point p1(200, 400, 15, 15, "Point 1");
    Point p2(500, 100, 15, 15, "Point 2");
    Point p3(1000, 275, 15, 15, "Point 3");

    sf::RectangleShape rectangle(sf::Vector2f(p1.getWidth(), p1.getHeight()));
    rectangle.setPosition({p1.getX(), p1.getY()});

    shapes.push_back(std::make_unique<sf::RectangleShape>(rectangle));
}

