#include "App.hpp"

#include <iostream>
#include <ranges>
#include <fstream>
#include <nlohmann/json.hpp>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "core/utils/Json.hpp"
#include "ui/common/Path.hpp"
#include "ui/elements/Divider.hpp"
#include "ui/elements/Element.hpp"
#include "ui/elements/LerpBezier.hpp"
#include "ui/elements/LineTool.hpp"
#include "ui/elements/Logo.hpp"
#include "ui/elements/Metrics.hpp"
#include "ui/regions/Canvas.hpp"
#include "ui/regions/Debug.hpp"
#include "core/events/EventBus.hpp"
#include "core/mappers/SFMLMapper.hpp"
#include "ui/common/RegionNamesEnum.hpp"
#include "ui/events/MousePressedEvent.hpp"
#include "ui/listeners/MouseClickRegionMatcherListener.hpp"

using json = nlohmann::json;

App::App(core::utils::Config cfg)
    : config(std::move(cfg)),
      window(sf::VideoMode({
                 config.windowWidth, config.windowHeight
             }), config.title, sf::Style::Titlebar | sf::Style::Close | sf::Style::None, sf::State::Windowed
      ) {
    window.setFramerateLimit(120);

    // Load point data from JSON
    std::vector<ui::common::Point> startPoints1;
    std::vector<ui::common::Point> startPoints2;
    ui::common::Path logoPath{"" "Logo"};

    try {
        std::ifstream f("points.json");
        if (!f.is_open()) {
            throw std::runtime_error("Could not open points.json");
        }
        json data = json::parse(f);

        startPoints1 = core::utils::json::parsePointArray(data["startPoints1"]);
        startPoints2 = core::utils::json::parsePointArray(data["startPoints2"]);
        logoPath = core::utils::json::parsePath(data["logoPath"]);
    } catch (const std::exception &e) {
        std::cerr << "Error loading points.json: " << e.what() << "\n";
    }

    // Bezier Curves
    auto quadBez = std::make_unique<ui::elements::QuadraticBezier>(std::move(startPoints1));
    auto lerpBez = std::make_unique<ui::elements::LerpBezier>(std::move(startPoints2));

    // Logo
    auto logo = std::make_unique<ui::elements::Logo>(std::move(logoPath));

    // Debug (Mem usage, mouse position etc)
    auto debug = std::make_unique<ui::elements::Metrics>();

    // Top left region
    std::vector<std::unique_ptr<ui::elements::Element> > topLeftRegionElements;
    topLeftRegionElements.push_back(std::move(quadBez));
    auto topLeftRegion = std::make_unique<ui::regions::Canvas>(window, std::move(topLeftRegionElements),
                                                               sf::Vector2f{10, 10}, sf::Vector2f{525, 390},
                                                               ui::common::toString(
                                                                   ui::common::RegionNamesEnum::PenTool
                                                               ),
                                                               ui::common::RegionNamesEnum::PenTool);

    // Top right region
    std::vector<std::unique_ptr<ui::elements::Element> > topRightRegionElements;
    topRightRegionElements.push_back(std::move(logo));
    auto topRightRegion = std::make_unique<ui::regions::Canvas>(window, std::move(topRightRegionElements),
                                                                sf::Vector2f{545, 10}, sf::Vector2f{525, 390},
                                                                ui::common::toString(ui::common::RegionNamesEnum::Logo),
                                                                ui::common::RegionNamesEnum::Logo);

    // Bottom left region
    std::vector<std::unique_ptr<ui::elements::Element> > bottomLeftRegionElements;
    bottomLeftRegionElements.push_back(std::move(lerpBez));
    auto bottomLeftRegion = std::make_unique<ui::regions::Canvas>(window, std::move(bottomLeftRegionElements),
                                                                  sf::Vector2f{10, 411}, sf::Vector2f{525, 390},
                                                                  ui::common::toString(
                                                                      ui::common::RegionNamesEnum::Lerp),
                                                                  ui::common::RegionNamesEnum::Lerp);

    // Bottom right region
    std::vector<std::unique_ptr<ui::elements::Element> > bottomRightRegionElements;
    auto bottomRightRegion = std::make_unique<ui::regions::Canvas>(window, std::move(bottomRightRegionElements),
                                                                   sf::Vector2f{545, 411}, sf::Vector2f{525, 390},
                                                                   ui::common::toString(
                                                                       ui::common::RegionNamesEnum::PenTool),
                                                                   ui::common::RegionNamesEnum::PenTool);

    // Side region
    std::vector<std::unique_ptr<ui::elements::Element> > sideRegionElements;
    sideRegionElements.push_back(std::move(debug));
    auto sideRegion = std::make_unique<ui::regions::Debug>(window, std::move(sideRegionElements), sf::Vector2f{1080, 0},
                                                           sf::Vector2f{200, 810});

    regions.push_back(std::move(topLeftRegion));
    regions.push_back(std::move(topRightRegion));
    regions.push_back(std::move(bottomLeftRegion));
    regions.push_back(std::move(bottomRightRegion));
    regions.push_back(std::move(sideRegion));
}

void App::run() {
    bindEvents();

    // Render loop
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void App::bindEvents() {

    // unique_ptr — owns the listener
    auto mouseClickRegionMatcherListener = std::make_unique<ui::listeners::MouseClickRegionMatcherListener>(regions);

    // grab raw observing pointer before the move (just the memory address of the pointer)
    auto* listenerPtr = mouseClickRegionMatcherListener.get();

    // lambda holds raw pointer — just observing the vector-owned object
    bus.subscribe<ui::events::MousePressedEvent>(
        [listenerPtr](const ui::events::MousePressedEvent &e) {
            listenerPtr->onEvent(e);
        }
    );

    // unique_ptr moves into vector — vector now owns it
    listeners.push_back(std::move(mouseClickRegionMatcherListener));
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
            for (auto &region: regions) {
                region->handleMouseMove(mousePos);
            }
        }

        // Handle mouse down
        if (const auto *e = event->getIf<sf::Event::MouseButtonPressed>()) {
            sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

            // New way to handle events more gracefully...
            bus.dispatch(ui::events::MousePressedEvent{
                core::mappers::SFMLMapper::toVector2f(mousePos),
                core::mappers::SFMLMapper::toMouseButton(e->button)
            });
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
