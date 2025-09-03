#include "App.hpp"

#include <iostream>
#include <ranges>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "ui/elements/Divider.hpp"
#include "ui/elements/Element.hpp"
#include "ui/elements/LerpBezier.hpp"
#include "ui/elements/Metrics.hpp"
#include "ui/regions/Canvas.hpp"
#include "ui/regions/Debug.hpp"


App::App(core::utils::Config config)
    : config(),
      window(sf::VideoMode({
                 config.windowWidth, config.windowHeight
             }), config.title, sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize, sf::State::Windowed
      ) {
    window.setFramerateLimit(120);

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

    // Bezier Curves
    auto quadBez = std::make_unique<ui::elements::QuadraticBezier>(std::move(startPoints1));
    auto lerpBez = std::make_unique<ui::elements::LerpBezier>(std::move(startPoints2));

    // Debug (Mem usage, mouse position etc)
    auto debug = std::make_unique<ui::elements::Metrics>();

    // Top region
    std::vector<std::unique_ptr<ui::elements::Element>> topRegionElements;
    topRegionElements.push_back(std::move(quadBez));
    auto topRegion = std::make_unique<ui::regions::Canvas>(window, std::move(topRegionElements), sf::Vector2f{10, 10}, sf::Vector2f{1060, 390}, "Quadratic");

    // Bottom region
    std::vector<std::unique_ptr<ui::elements::Element>> bottomRegionElements;
    bottomRegionElements.push_back(std::move(lerpBez));
    auto bottomRegion = std::make_unique<ui::regions::Canvas>(window, std::move(bottomRegionElements), sf::Vector2f{10, 411}, sf::Vector2f{1060, 390}, "Linear Interpolation");
    
    // Side region
    std::vector<std::unique_ptr<ui::elements::Element>> sideRegionElements;
    sideRegionElements.push_back(std::move(debug));
    auto sideRegion = std::make_unique<ui::regions::Debug>(window, std::move(sideRegionElements), sf::Vector2f{1080, 0}, sf::Vector2f{200, 810});

    regions.push_back(std::move(topRegion));
    regions.push_back(std::move(bottomRegion));
    regions.push_back(std::move(sideRegion));
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
                if (
                    mousePos.y > region->getPosition().y && mousePos.y < (region->getSize().y + region->getPosition().y)
                    && mousePos.x > region->getPosition().x && mousePos.x < (region->getSize().x + region->getPosition().x)
                ) {
                    region->handleMouseButtonPressed(mousePos);
                }
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
