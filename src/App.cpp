#include "App.hpp"

#include <iostream>
#include <ranges>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "ui/common/Path.hpp"
#include "ui/elements/Divider.hpp"
#include "ui/elements/Element.hpp"
#include "ui/elements/LerpBezier.hpp"
#include "ui/elements/LineTool.hpp"
#include "ui/elements/Logo.hpp"
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

    // TODO: move these to some sort of data file, then read them in?
    std::vector<ui::common::Point> startPoints1 = {
        {"Point 1", {50, 350}, {15, 15}},
        {"Point 2", {250, 50}, {15, 15}},
        {"Point 3", {450, 275}, {15, 15}}
    };

    std::vector<ui::common::Point> startPoints2 = {
        {"Point 3", {50, 761}, {15, 15}},
        {"Point 4", {250, 461}, {15, 15}},
        {"Point 5", {450, 686}, {15, 15}}
    };

    std::vector<ui::common::Point> startPoints3 = {
        {"Point 6", {600, 711}, {15, 15}},
        {"Point 7", {961, 486}, {15, 15}}
    };

    // Logo
    ui::common::Path logoPath{"Logo"};
    logoPath.segments.push_back(ui::common::Segment{ui::common::SegmentType::LINE, {
        {"Point 1", {600, 350}, {5, 5}},
        {"Point 2", {600, 100}, {5, 5}},
    }});

    logoPath.segments.push_back(ui::common::Segment{ui::common::SegmentType::LINE, {
        {"Point 2", {600, 100}, {5, 5}},
        {"Point 3", {675, 100}, {5, 5}},
    }});

    logoPath.segments.push_back(ui::common::Segment{ui::common::SegmentType::CURVE, {
        {"Point 3", {675, 100}, {5, 5}},
        {"Point 4", {665, 175}, {5, 5}},
    }});

    logoPath.segments.push_back(ui::common::Segment{ui::common::SegmentType::CURVE, {
        {"Point 4", {665, 175}, {5, 5}},
        // control point here
        {"Point 5", {750, 100}, {5, 5}},
    }});

    logoPath.segments.push_back(ui::common::Segment{ui::common::SegmentType::CURVE, {
        {"Point 5", {750, 100}, {5, 5}},
        // control point here
        {"Point 6", {850, 175}, {5, 5}},
    }});

    logoPath.segments.push_back(ui::common::Segment{ui::common::SegmentType::LINE, {
        {"Point 6", {850, 175}, {5, 5}},
        {"Point 7", {850, 350}, {5, 5}},
    }});

    logoPath.segments.push_back(ui::common::Segment{ui::common::SegmentType::LINE, {
        {"Point 7", {850, 350}, {5, 5}},
        {"Point 8", {775, 350}, {5, 5}},
    }});

    logoPath.segments.push_back(ui::common::Segment{ui::common::SegmentType::LINE, {
        {"Point 8", {775, 350}, {5, 5}},
        {"Point 9", {775, 225}, {5, 5}},
    }});

    logoPath.segments.push_back(ui::common::Segment{ui::common::SegmentType::CURVE, {
        {"Point 9", {775, 225}, {5, 5}},
        {"Point 10", {675, 225}, {5, 5}}
    }});

    logoPath.segments.push_back(ui::common::Segment{ui::common::SegmentType::LINE, {
        {"Point 10", {675, 225}, {5, 5}},
        {"Point 11", {675, 350}, {5, 5}}
    }});

    logoPath.segments.push_back(ui::common::Segment{ui::common::SegmentType::LINE, {
        {"Point 11", {675, 350}, {5, 5}},
        {"Point 12", {600, 350}, {5, 5}}
    }});

    // Bezier Curves
    auto quadBez = std::make_unique<ui::elements::QuadraticBezier>(std::move(startPoints1));
    auto lerpBez = std::make_unique<ui::elements::LerpBezier>(std::move(startPoints2));

    // Logo
    auto logo = std::make_unique<ui::elements::Logo>(std::move(logoPath));

    // Debug (Mem usage, mouse position etc)
    auto debug = std::make_unique<ui::elements::Metrics>();

    // Top left region
    std::vector<std::unique_ptr<ui::elements::Element>> topLeftRegionElements;
    topLeftRegionElements.push_back(std::move(quadBez));
    auto topLeftRegion = std::make_unique<ui::regions::Canvas>(window, std::move(topLeftRegionElements), sf::Vector2f{10, 10}, sf::Vector2f{525, 390}, "Quadratic");

    // Top right region
    std::vector<std::unique_ptr<ui::elements::Element>> topRightRegionElements;
    topRightRegionElements.push_back(std::move(logo));
    auto topRightRegion = std::make_unique<ui::regions::Canvas>(window, std::move(topRightRegionElements), sf::Vector2f{545, 10}, sf::Vector2f{525, 390}, "Logo");

    // Bottom left region
    std::vector<std::unique_ptr<ui::elements::Element>> bottomLeftRegionElements;
    bottomLeftRegionElements.push_back(std::move(lerpBez));
    auto bottomLeftRegion = std::make_unique<ui::regions::Canvas>(window, std::move(bottomLeftRegionElements), sf::Vector2f{10, 411}, sf::Vector2f{525, 390}, "Linear Interpolation");

    // Bottom right region
    std::vector<std::unique_ptr<ui::elements::Element>> bottomRightRegionElements;
    auto bottomRightRegion = std::make_unique<ui::regions::Canvas>(window, std::move(bottomRightRegionElements), sf::Vector2f{545, 411}, sf::Vector2f{525, 390}, this->APP_REGION_PEN_TOOL);
    
    // Side region
    std::vector<std::unique_ptr<ui::elements::Element>> sideRegionElements;
    sideRegionElements.push_back(std::move(debug));
    auto sideRegion = std::make_unique<ui::regions::Debug>(window, std::move(sideRegionElements), sf::Vector2f{1080, 0}, sf::Vector2f{200, 810});

    regions.push_back(std::move(topLeftRegion));
    regions.push_back(std::move(topRightRegion));
    regions.push_back(std::move(bottomLeftRegion));
    regions.push_back(std::move(bottomRightRegion));
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

            std::cout << "mousePos: " << mousePos.x << ", " << mousePos.y << std::endl;

            for (auto &region: regions) {

                std::cout << "regionPos: " << region->getPosition().x << ", " << region->getPosition().y << std::endl;

                if (
                    mousePos.x > region->getPosition().x && mousePos.x < (region->getSize().x + region->getPosition().x)
                    && mousePos.y > region->getPosition().y && mousePos.y < (region->getSize().y + region->getPosition().y)
                ) {
                    std::cout << "Region matched!" << std::endl;

                    // Some hacky code to force pen tool behavior on the Canvas instance
                    if (region->getName() == this->APP_REGION_PEN_TOOL) {
                        auto* canvas = dynamic_cast<ui::regions::Canvas*>(region.get());
                        if (canvas) {

                            // Only create if there's no active tool yet
                            if (!canvas->getActiveTool()) {
                                canvas->setActiveTool(std::make_unique<ui::elements::LineTool>());
                            }

                            if (canvas->getActiveTool() != nullptr) {
                                canvas->getActiveTool()->handleMouseButtonPressed(mousePos);
                            }
                        }
                    }
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
