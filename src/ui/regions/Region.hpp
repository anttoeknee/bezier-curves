#pragma once
#include <utility>

#include "../elements/Element.hpp"

struct Region {

    sf::Vector2f position;
    sf::Vector2f size;

    std::vector<std::unique_ptr<Element> > elements;

    sf::RenderWindow &target;

    explicit Region(sf::RenderWindow &target);

    virtual void draw() const = 0;

    virtual void update() const = 0;

    void addElement(std::unique_ptr<Element> element) {
        elements.push_back(std::move(element));
    }

    virtual void handleMouseButtonPressed(sf::Vector2f &mousePos) = 0;

    virtual void handleMouseButtonReleased() = 0;

    const std::vector<std::unique_ptr<Element> > &getElements() const { return elements; }

    virtual ~Region() = default;
};

// TODO: maybe move this at a later date?
inline Region::Region(sf::RenderWindow &target) : target(target) {}
