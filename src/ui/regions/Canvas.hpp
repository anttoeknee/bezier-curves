#pragma once
#include "Region.hpp"
#include "../elements/LineTool.hpp"
#include "../elements/QuadraticBezier.hpp"

namespace ui::regions {
    class Canvas : public Region {
        std::vector<common::Point> startPoints{};
        std::unique_ptr<elements::Element> activeTool;

    public:
        Canvas(
            sf::RenderWindow &target,
            std::vector<std::unique_ptr<elements::Element> > &&elements,
            sf::Vector2f position,
            sf::Vector2f size,
            std::string name
        );

        ~Canvas() override;

        void handleMouseMove(sf::Vector2f &mousePos) override;

        void handleMouseButtonReleased() override;

        void handleMouseButtonPressed(sf::Vector2f &mousePos) override;

        void draw() override;

        void update() override;

        void setActiveTool(std::unique_ptr<elements::Element> &&element);

        elements::Element* getActiveTool() const {
            return activeTool.get();
        }
    };
}

