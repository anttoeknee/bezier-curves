#include "Canvas.hpp"
#include "../elements/QuadraticBezier.hpp"
#include "../elements/LerpBezier.hpp"
#include "../elements/Divider.hpp"
#include "../utils/ScopedWindowClipping.hpp"
#include "../../core/utils/AssetManager.hpp"

ui::regions::Canvas::Canvas(
        sf::RenderWindow &target,
        std::vector<std::unique_ptr<elements::Element>> &&elements,
        sf::Vector2f position,
        sf::Vector2f size,
        std::string name
    ): Region(target, std::move(elements)) {

    _position = position;
    _size = size;
    _name = name;
}

ui::regions::Canvas::~Canvas() = default;

void ui::regions::Canvas::handleMouseMove(sf::Vector2f &mousePos) {
}

void ui::regions::Canvas::handleMouseButtonPressed(sf::Vector2f &mousePos) {

    // Pass to all elements (maybe we narrow down scope here like we do for regions?)
    for (auto &element: elements) {
        element->handleMouseButtonPressed(mousePos);
    }


}

void ui::regions::Canvas::handleMouseButtonReleased() {
    for (auto &element: elements) {
        element->handleMouseButtonReleased();
    }
}

void ui::regions::Canvas::draw() const {
    sf::Vector2f windowSize = static_cast<sf::Vector2f>(target.getSize());

    sf::View oldView = target.getView();

    utils::ScopedWindowClipping sWinClip(target, _position, windowSize);

    sf::RectangleShape background;
    background.setPosition(_position);
    background.setSize(_size);
    background.setFillColor(sf::Color(50, 50, 50)); // Dark gray background

    // Not sure some simple text warrants an element?
    // TODO: break this down so it can be used across draw and update
    sf::Font font = core::utils::AssetManager::loadEmbeddedFont();
    sf::Text title(font);
    title.setString(_name);
    title.setCharacterSize(16);
    title.setFillColor(sf::Color::White);
    title.setPosition({_position.x + 10, _position.y + 10});


    target.draw(background);

    for (auto &element: elements) {
        element->draw(target, _position);
    }

    if (activeTool != nullptr) {
        activeTool->draw(target, _position);
    }

    target.draw(title);

    target.setView(oldView);
}

void ui::regions::Canvas::update() const {
    for (auto &element: elements) {
        element->update(target, _position);
    }

    if (activeTool != nullptr) {
        activeTool->update(target, _position);
    }
}

void ui::regions::Canvas::setActiveTool(std::unique_ptr<elements::Element> &&element) {
    activeTool = std::move(element);
}


