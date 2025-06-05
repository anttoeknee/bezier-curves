#pragma once
#include <utility>

#include "../elements/Element.hpp"


namespace ui::regions {
    /**
     * @brief Base region struct which all other regions should extend
     *
     * A Region defines an area of the UI to be drawn in the window based upon its position and
     * size properties.
     *
     * In turn, the Region will house Elements to be drawn relatively within the Region and is
     * responsible for doing so.
     *
     * The App is then responsible for drawing the Regions
     */
    struct Region {
        sf::Vector2f _position;
        sf::Vector2f _size;

        std::vector<std::unique_ptr<elements::Element> > elements;

        sf::RenderWindow &target;

        explicit Region(sf::RenderWindow &target);

        virtual void draw() const = 0;

        virtual void update() const = 0;

        void addElement(std::unique_ptr<elements::Element> element) {
            elements.push_back(std::move(element));
        }

        virtual void handleMouseMove(sf::Vector2f &mousePos) = 0;

        virtual void handleMouseButtonPressed(sf::Vector2f &mousePos) = 0;

        virtual void handleMouseButtonReleased() = 0;

        const std::vector<std::unique_ptr<elements::Element> > &getElements() const { return elements; }

        virtual ~Region() = default;
    };
}


// TODO: maybe move this at a later date?
inline ui::regions::Region::Region(sf::RenderWindow &target) : target(target) {
}
