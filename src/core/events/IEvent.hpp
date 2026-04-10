#pragma once

namespace core::events {
    struct IEvent {
        virtual ~IEvent() = default;
    };
}
