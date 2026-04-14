#pragma once

#include "../../core/listeners/IListener.hpp"
#include "../events/MousePressedEvent.hpp"
#include "../regions/Region.hpp"

namespace ui::listeners {
    class MouseClickRegionMatcherListener : public core::listeners::IListener {
    public:
        MouseClickRegionMatcherListener(std::vector<std::unique_ptr<regions::Region> > &regions)
            : regions(regions) {
        }

        void onEvent(const events::MousePressedEvent &event);

    private:
        std::vector<std::unique_ptr<ui::regions::Region> > &regions;
    };
}
