#include "App.hpp"

#include <iostream>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "ui/elements/Element.hpp"
#include "ui/regions/Canvas.hpp"
#include "ui/regions/Debug.hpp"


App::App(core::utils::Config config)
    : config(),
      window(sf::VideoMode({
                 config.windowWidth, config.windowHeight
             }), "Bezier Curves", sf::Style::Titlebar | sf::Style::Close
      ) {
    window.setFramerateLimit(60);

    // Bezier Curves
    regions.push_back(std::make_unique<ui::regions::Canvas>(window, sf::Vector2f{0, 0}, sf::Vector2f{1080, 400}));
    regions.push_back(std::make_unique<ui::regions::Canvas>(window, sf::Vector2f{0, 401}, sf::Vector2f{1080, 400}));

    // Debug
    regions.push_back(std::make_unique<ui::regions::Debug>(window));
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

        // Handle mouse move
        if (event->is<sf::Event::MouseMoved>()) {
            sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
            for (auto& region : regions) {
                region->handleMouseMove(mousePos);
            }
        }

        // Handle mouse down
        if (event->is<sf::Event::MouseButtonPressed>()) {
            sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
            for (auto &region: regions) {
                region->handleMouseButtonPressed(mousePos);
            }
        }

        // Handle mouse release
        if (event->is<sf::Event::MouseButtonReleased>()) {
            for (auto &region: regions) {
                region->handleMouseButtonReleased();
            }
        }
    }
}

void App::render() {
    window.clear();

    for (auto &region: regions) {
        region->draw();
    }
    window.display();
}

void App::update() {
    for (auto &region: regions) {
        region->update();
    }
}
