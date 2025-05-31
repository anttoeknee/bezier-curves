#include "App.h"

#include <iostream>

#include "core/utils/Mem.hpp"
#include "elements/Debug.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "elements/Element.hpp"
#include "elements/QuadraticBezier.hpp"

App::App(Config config)
    : config(),
      window(sf::VideoMode({
                 config.windowHeight, config.windowWidth
             }), "Bezier Curves", sf::Style::Titlebar | sf::Style::Close
      ) {
    window.setFramerateLimit(60);

    // TODO: move to a scene object
    std::vector<PointData> startPoints = {
        {"Point 1", {200, 400}, {15, 15}},
        {"Point 2", {500, 100}, {15, 15}},
        {"Point 3", {1000, 275}, {15, 15}}
    };

    // TODO: move to a scene object
    elements.push_back(std::make_unique<QuadraticBezier>(std::move(startPoints)));
    elements.push_back(std::make_unique<Debug>());
}

void App::run() {
    // Render loop
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void App::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        // Close the app...
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        // Handle mouse down
        if (event->is<sf::Event::MouseButtonPressed>()) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            for (auto &element: elements) {
                element->handleMouseButtonPressed(mousePos);
            }
        }

        // Handle mouse release
        if (event->is<sf::Event::MouseButtonReleased>()) {
            for (auto &element: elements) {
                element->handleMouseButtonReleased();
            }
        }
    }
}

void App::render() {
    window.clear();

    for (auto &element: elements) {
        element->draw(window);
    }
    window.display();
}

void App::update() {
    for (auto &element: elements) {
        element->update(window);
    }
}
