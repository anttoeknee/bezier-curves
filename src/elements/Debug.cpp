#include "Debug.hpp"
#include "../core/utils/Mem.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

void Debug::draw(sf::RenderWindow &target) const {
    target.draw(container);
    target.draw(text);
}

void Debug::update(sf::RenderWindow &target) const {

    sf::View view = target.getDefaultView();
    sf::Vector2f vSize = view.getSize();
    float vpX = vSize.x;

    container = sf::RectangleShape({200, 900});
    container.setPosition({vpX - 200, 0});
    container.setFillColor(sf::Color::White);

    std::string memUsage = getMemUsage();

    text.setString("Memory usage: " + memUsage);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Blue);
    text.setPosition({vpX - 180, 10});
}

void Debug::handleMouseButtonPressed(sf::Vector2i &mousePos) {
}

void Debug::handleMouseButtonReleased() {
}

Debug::Debug(): font("/System/Library/Fonts/SFNS.ttf"), text(font) {
}
