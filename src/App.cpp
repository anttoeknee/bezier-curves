
#include "../includes/App.hpp"

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
    // draw canvas/tools here
    window.display();
}

void App::update() {
    // TODO: changes to positions etc here
}

