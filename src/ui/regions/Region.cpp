#include "Region.hpp"

ui::regions::Region::Region(
        sf::RenderWindow &target,
        std::vector<std::unique_ptr<elements::Element>> &&elements
    ): target(target), elements(std::move(elements)) {
}

