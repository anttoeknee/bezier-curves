#include "App.hpp"

#include <iostream>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "elements/Element.hpp"
#include "scenes/Bezier.hpp"


App::App(Config config)
    : config(),
      window(sf::VideoMode({
                 config.windowWidth, config.windowHeight
             }), "Bezier Curves", sf::Style::Titlebar | sf::Style::Close
      ) {
    window.setFramerateLimit(60);

    // Bezier Curves
    scenes.push_back(std::make_unique<Bezier>());
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
            for (auto &scene: scenes) {
                scene->handleMouseButtonPressed(mousePos);
            }
        }

        // Handle mouse release
        if (event->is<sf::Event::MouseButtonReleased>()) {
            for (auto &scene: scenes) {
                scene->handleMouseButtonReleased();
            }
        }
    }
}

void App::render() {
    window.clear();

    for (auto &scene: scenes) {
        scene->draw(window);
    }
    window.display();
}

void App::update() {
    for (auto &scene: scenes) {
        scene->update(window);
    }
}
