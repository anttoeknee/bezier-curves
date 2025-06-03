#pragma once
#include <utility>

#include "../elements/Element.hpp"

struct Region {

    float x, y;
    float width, height;

    std::vector<std::unique_ptr<Element> > elements;

    explicit Region() = default;

    virtual void draw(sf::RenderWindow &target) const = 0;

    virtual void update(sf::RenderWindow &target) const = 0;

    void addElement(std::unique_ptr<Element> element) {
        elements.push_back(std::move(element));
    }

    virtual void handleMouseButtonPressed(sf::Vector2i &mousePos) = 0;

    virtual void handleMouseButtonReleased() = 0;

    const std::vector<std::unique_ptr<Element> > &getElements() const { return elements; }

    virtual ~Region() = default;
};
