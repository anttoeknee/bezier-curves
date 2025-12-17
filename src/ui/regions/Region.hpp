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
     * The Region will own these elements
     *
     * The App is then responsible for drawing the Regions
     */
    class Region {
    protected:
        sf::Vector2f _position;
        sf::Vector2f _size;
        std::string _name;

        std::vector<std::unique_ptr<elements::Element> > elements;

        sf::RenderWindow &target;

    public:

        Region(sf::RenderWindow &target, std::vector<std::unique_ptr<elements::Element>> &&elements);

        virtual void draw() = 0;

        virtual void update() = 0;

        void addElement(std::unique_ptr<elements::Element> element) {
            elements.push_back(std::move(element));
        }

        virtual void handleMouseMove(sf::Vector2f &mousePos) = 0;

        virtual void handleMouseButtonPressed(sf::Vector2f &mousePos) = 0;

        virtual void handleMouseButtonReleased() = 0;

        const std::vector<std::unique_ptr<elements::Element> > &getElements() const { return elements; }

        sf::Vector2f getPosition() const { return _position; }

        sf::Vector2f getSize() const { return _size; }

        std::string getName() const { return _name; }

        virtual ~Region() = default;
    };
}
