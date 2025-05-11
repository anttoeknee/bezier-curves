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
        text.setCharacterSize(24); // in pixels, not points!
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
    // Initial state for points
    // TODO: move point data somewhere else
    Point p1(200, 400, 15, 15, "Point 1");
    Point p2(500, 100, 15, 15, "Point 2");
    Point p3(1000, 275, 15, 15, "Point 3");

    sf::RectangleShape rectangle(sf::Vector2f(p1.getWidth(), p1.getHeight()));
    rectangle.setPosition({p1.getX(), p1.getY()});

    shapes.push_back(std::make_unique<sf::RectangleShape>(rectangle));
}
