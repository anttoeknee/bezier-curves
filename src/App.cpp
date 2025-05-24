#include <SFML/Graphics/Rect.hpp>

#include "../includes/App.h"

#include <iostream>

#include "../includes/utils/Mem.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

App::App(Config config)
    : config(), window(sf::VideoMode({config.windowHeight, config.windowWidth}), "Bezier Curves") {
    window.setFramerateLimit(60);

    startPoints = {
        {"Point 1", {200, 400}, {15, 15}},
        {"Point 2", {500, 100}, {15, 15}},
        {"Point 3", {1000, 275}, {15, 15}}
    };
}

void App::run() {

    // Initial state
    for (auto &point: startPoints) {
        sf::RectangleShape rect(sf::Vector2f(point.size.x, point.size.y));
        rect.setPosition({point.position.x, point.position.y});
        rect.setFillColor(sf::Color::White);
        shapes.push_back(std::make_unique<sf::RectangleShape>(rect));
    }

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

            // TODO: relocate this
            // Mousedown, over a shape...
            for (auto &shape: shapes) {

                // Determine if we've mouse-downed on this shape
                if (shape->getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {

                    // Update our bool
                    isDragging = true;

                    // Make sure we don't get jumpy movement of the shape
                    draggedShape = shape.get();
                    dragOffset = {
                        static_cast<float>(mousePos.x) - draggedShape->getPosition().x,
                        static_cast<float>(mousePos.y) - draggedShape->getPosition().y
                    };
                    break;
                }
            }
        }

        // Handle mouse release
        if (event->is<sf::Event::MouseButtonReleased>()) {

            // Reset our bool and dragged shape
            isDragging = false;
            draggedShape = nullptr;
        }
    }
}

void App::render() {
    window.clear();

    for (auto &shape: shapes) {
        window.draw(*shape);
    }

    // TODO: relocate
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

    // Handle dragging
    if (isDragging && draggedShape) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        draggedShape->setPosition({mousePos.x - dragOffset.x, mousePos.y - dragOffset.y});
    }

}
