#include "App.hpp"

#include <iostream>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "elements/Element.hpp"
#include "regions/Bezier.hpp"
#include "regions/Debug.hpp"


App::App(Config config)
    : config(),
      window(sf::VideoMode({
                 config.windowWidth, config.windowHeight
             }), "Bezier Curves", sf::Style::Titlebar | sf::Style::Close
      ) {
    window.setFramerateLimit(60);

    // Bezier Curves
    regions.push_back(std::make_unique<Bezier>());

    // Debug
    regions.push_back(std::make_unique<Debug>());
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
            for (auto &scene: regions) {
                scene->handleMouseButtonPressed(mousePos);
            }
        }

        // Handle mouse release
        if (event->is<sf::Event::MouseButtonReleased>()) {
            for (auto &scene: regions) {
                scene->handleMouseButtonReleased();
            }
        }
    }
}

void App::render() {
    window.clear();

    for (auto &scene: regions) {
        scene->draw(window);
    }
    window.display();
}

void App::update() {
    for (auto &scene: regions) {
        scene->update(window);
    }
}
