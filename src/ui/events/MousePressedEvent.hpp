#pragma once

#include "../../core/common/MouseButton.hpp"
#include "../../core/common/Vector2f.hpp"
#include "../../core/events/IEvent.hpp"

namespace ui::events {
    struct MousePressedEvent : public core::events::IEvent {
        core::Vector2f position;
        core::MouseButton button;

        MousePressedEvent(core::Vector2f position, core::MouseButton button)
            : position(position), button(button) {
        }
    };
}

