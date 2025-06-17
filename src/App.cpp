#include "App.hpp"

#include <iostream>
#include <ranges>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "ui/elements/Divider.hpp"
#include "ui/elements/Element.hpp"
#include "ui/elements/LerpBezier.hpp"
#include "ui/regions/Canvas.hpp"
#include "ui/regions/Debug.hpp"


App::App(core::utils::Config config)
    : config(),
      window(sf::VideoMode({
                 config.windowWidth, config.windowHeight
             }), "Bezier Curves", sf::Style::Titlebar | sf::Style::Close
      ) {
    window.setFramerateLimit(60);

    std::vector<ui::common::Point> startPoints1 = {
        {"Point 1", {50, 350}, {15, 15}},
        {"Point 2", {350, 50}, {15, 15}},
        {"Point 3", {850, 275}, {15, 15}}
    };

    std::vector<ui::common::Point> startPoints2 = {
        {"Point 3", {100, 750}, {15, 15}},
        {"Point 4", {750, 425}, {15, 15}},
        {"Point 5", {850, 755}, {15, 15}}
    };

    // Divider to separate Canvas'
    auto divider = std::make_unique<ui::elements::Divider>();

    // Bezier Curves
    auto quadBez = std::make_unique<ui::elements::QuadraticBezier>(std::move(startPoints1));
    auto lerpBez = std::make_unique<ui::elements::LerpBezier>(std::move(startPoints2));

    // Top region
    std::vector<std::unique_ptr<ui::elements::Element>> topRegionElements;
    topRegionElements.push_back(std::move(quadBez));
    auto topRegion = std::make_unique<ui::regions::Canvas>(window, topRegionElements, sf::Vector2f{0, 0}, sf::Vector2f{1080, 400});

    // Bottom region
    std::vector<std::unique_ptr<ui::elements::Element>> bottomRegionElements;
    bottomRegionElements.push_back(std::move(lerpBez));
    auto bottomRegion = std::make_unique<ui::regions::Canvas>(window, bottomRegionElements, sf::Vector2f{0, 401}, sf::Vector2f{1080, 400});
    
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
