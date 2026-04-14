#include "MouseClickRegionMatcherListener.hpp"

#include <iostream>

#include "../../App.hpp"
#include "../common/RegionNamesEnum.hpp"
#include "../regions/Canvas.hpp"

void ui::listeners::MouseClickRegionMatcherListener::onEvent(const events::MousePressedEvent &event) {

    std::cout << "MouseClickRegionMatcherListener::onEvent()" << std::endl;

    for (auto &region: regions) {
        //std::cout << "regionPos: " << region->getPosition().x << ", " << region->getPosition().y << std::endl;

        if (
            event.position.x > region->getPosition().x && event.position.x < (
                region->getSize().x + region->getPosition().x)
            && event.position.y > region->getPosition().y && event.position.y < (
                region->getSize().y + region->getPosition().y)
        ) {
            //  std::cout << "Region matched!" << std::endl;

            // Some hacky code to force pen tool behavior on the Canvas instance
            switch (region->getId()) {
                case common::RegionNamesEnum::PenTool: {
                    auto *canvas = dynamic_cast<regions::Canvas *>(region.get());
                    if (canvas) {
                        // Only create if there's no active tool yet
                        if (!canvas->getActiveTool()) {
                            canvas->setActiveTool(std::make_unique<elements::LineTool>());
                        }

                        if (canvas->getActiveTool() != nullptr) {
                            canvas->getActiveTool()->handleMouseButtonPressed(event.position);
                        }
                    }
                    break;
                }
                case common::RegionNamesEnum::Lerp:
                    break;
                case common::RegionNamesEnum::Quad:
                    break;
                case common::RegionNamesEnum::Logo:
                    break;
                case common::RegionNamesEnum::Debug:
                    break;

            }


            region->handleMouseButtonPressed(event.position);
        }
    }
}
