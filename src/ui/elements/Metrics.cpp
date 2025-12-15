#include "Metrics.hpp"

#include "../../core/utils/AssetManager.hpp"
#include "../../core/utils/Mem.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

// TODO: pass origin from region into constructor
ui::elements::Metrics::Metrics(): font(core::utils::AssetManager::loadEmbeddedFont()), memText(font), mousePosText(font) {
    // TODO: see if we can get the position before onMove
    mousePosition({0, 0});
}

void ui::elements::Metrics::draw(sf::RenderWindow &target, sf::Vector2f origin) const {
    target.draw(memText);
    target.draw(mousePosText);
}

void ui::elements::Metrics::update(sf::RenderWindow &target, sf::Vector2f origin) {
    memoryUsage(origin);
}

void ui::elements::Metrics::memoryUsage(sf::Vector2f origin) const {
    std::string memUsage = core::utils::getMemUsage();

    memText.setString("Memory usage: " + memUsage);
    memText.setCharacterSize(16);
    memText.setFillColor(sf::Color::Blue);
    memText.setPosition({origin.x + 10, 10});
}

void ui::elements::Metrics::mousePosition(sf::Vector2f mousePos) const {

    mousePosText.setString(std::format("Mouse (x,y): {:.0f},{:.0f}", mousePos.x, mousePos.y));
    mousePosText.setCharacterSize(16);
    mousePosText.setFillColor(sf::Color::Blue);
    mousePosText.setPosition({1090, 40}); // TODO: use origin from constructor when done
}

void ui::elements::Metrics::handleMouseMove(sf::Vector2f &mousePos) {
    mousePosition(mousePos);
}

void ui::elements::Metrics::handleMouseButtonPressed(sf::Vector2f &mousePos) {
}

void ui::elements::Metrics::handleMouseButtonReleased() {
}
