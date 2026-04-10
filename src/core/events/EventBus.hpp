#pragma once
#include <functional>
#include <typeindex>
#include <unordered_map>

#include "IEvent.hpp"

namespace core::events {
    class EventBus {
    public:

        template<typename TEvent>
        void subscribe(std::function<void(const TEvent &)> listener) {
            listeners[typeid(TEvent)].push_back(
                [listener](const IEvent &e) {
                    listener(static_cast<const TEvent &>(e));
                }
            );
        }

        template<typename TEvent>
        void dispatch(const TEvent &event) {
            auto it = listeners.find(typeid(TEvent));
            if (it != listeners.end()) {
                for (auto &listener: it->second) {
                    listener(event);
                }
            }
        }

    private:
        std::unordered_map<std::type_index, std::vector<std::function<void(const IEvent &)> > > listeners;
    };
}
