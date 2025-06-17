#include "Canvas.hpp"
#include "../elements/QuadraticBezier.hpp"
#include "../elements/LerpBezier.hpp"
#include "../elements/Divider.hpp"
#include "../utils/ScopedWindowClipping.hpp"

ui::regions::Canvas::Canvas(sf::RenderWindow &target, std::vector<std::unique_ptr<elements::Element> > &elements, sf::Vector2f position, sf::Vector2f size): Region(target, elements) {

    _position = position;
    _size = size;

    // std::vector<common::Point> startPoints1 = {
    //     {"Point 1", {50, 350}, {15, 15}},
    //     {"Point 2", {350, 50}, {15, 15}},
    //     {"Point 3", {850, 275}, {15, 15}}
    // };
    //
    // std::vector<common::Point> startPoints2 = {
    //     {"Point 3", {100, 750}, {15, 15}},
    //     {"Point 4", {750, 425}, {15, 15}},
    //     {"Point 5", {850, 755}, {15, 15}}
    // };
    //
    // elements.push_back(std::make_unique<elements::Divider>());
    // elements.push_back(std::make_unique<elements::QuadraticBezier>(std::move(startPoints1)));
    // elements.push_back(std::make_unique<elements::LerpBezier>(std::move(startPoints2)));
}

ui::regions::Canvas::~Canvas() = default;

void ui::regions::Canvas::handleMouseMove(sf::Vector2f &mousePos) {
}

void ui::regions::Canvas::handleMouseButtonPressed(sf::Vector2f &mousePos) {
    sf::Vector2f localMouse = mousePos - _position;
    for (auto &element : elements) {
        element->handleMouseButtonPressed(localMouse);
    }
}

void ui::regions::Canvas::handleMouseButtonReleased() {
    for (auto &element : elements) {
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

    target.draw(background);

    for (auto &element : elements) {
        element->draw(target, _position);
    }

    target.setView(oldView);
}

void ui::regions::Canvas::update() const {
    for (auto &element : elements) {
        element->update(target, _position);
    }
}





