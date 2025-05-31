#include "Debug.hpp"

#include <iostream>

#include "../core/utils/Mem.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

void Debug::draw(sf::RenderWindow &target) const {
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

        target.draw(text);
    } catch (const std::exception &e) {
        // TODO: figure out what sending something to std::cerr does
        std::cerr << e.what() << std::endl;
    }
}

void Debug::update(sf::RenderWindow &target) const {
}

void Debug::handleMouseButtonPressed(sf::Vector2i &mousePos) {
}

void Debug::handleMouseButtonReleased() {
}

Debug::Debug() = default;
