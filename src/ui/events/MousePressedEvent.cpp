#include "../../core/common/MouseButton.hpp"
#include "../../core/common/Vector2f.hpp"
#include "../../core/events/IEvent.hpp"

using namespace core;

struct MousePressedEvent : public events::IEvent {
    Vector2f position;
    MouseButton button;
};
