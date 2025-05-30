#include <SFML/Graphics/Rect.hpp>

#include "../includes/App.h"

#include <iostream>

#include "../includes/utils/Mem.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "core/math/Geometry.h"
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

    element = std::make_unique<QuadraticBezier>(std::move(startPoints));
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
            element->handleMouseButtonPressed(mousePos);
        }

        // Handle mouse release
        if (event->is<sf::Event::MouseButtonReleased>()) {
            element->handleMouseButtonReleased();
        }
    }
}

void App::render() {
    window.clear();

    // Quadratic Bezier
    element->draw(window);

    // Debug info
    std::string memUsage = getMemUsage();
    try {
        // Find font on OS
        // TODO: create platform specific implementation
        std::string fontPath = "/System/Library/Fonts/SFNS.ttf";
        sf::Font fontSfProTextReg(fontPath);
        sf::Text text(fontSfProTextReg);

        text.setString(memUsage);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        text.setPosition({10, 10});

        window.draw(text);
    } catch (const std::exception &e) {
        // TODO: figure out what sending something to std::cerr does
        std::cerr << e.what() << std::endl;
    }

    window.display();
}

void App::update() {

    element->update(window);
}
