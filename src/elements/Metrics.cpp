#include "Metrics.hpp"
#include "../core/utils/Mem.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

void Metrics::draw(sf::RenderWindow &target, sf::Vector2f origin) const {
    target.draw(text);
}

void Metrics::update(sf::RenderWindow &target, sf::Vector2f origin) const {

    std::string memUsage = getMemUsage();

    text.setString("Memory usage: " + memUsage);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Blue);
    text.setPosition({origin.x + 10, 10});
}

void Metrics::handleMouseButtonPressed(sf::Vector2f &mousePos) {
}

void Metrics::handleMouseButtonReleased() {
}

Metrics::Metrics(): font("/System/Library/Fonts/SFNS.ttf"), text(font) {
}
