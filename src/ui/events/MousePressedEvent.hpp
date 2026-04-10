#pragma once

namespace ui::events {
    struct MousePressedEvent : public core::events::IEvent {
        core::Vector2f position;
        core::MouseButton button;

        MousePressedEvent(core::Vector2f position, core::MouseButton button)
            : position(position), button(button) {
        }
    };
}
