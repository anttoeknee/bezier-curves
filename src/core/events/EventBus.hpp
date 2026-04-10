#pragma once
#include <functional>
#include <typeindex>
#include <unordered_map>

#include "IEvent.hpp"

class EventBus {
public:
    EventBus();

    template<typename TEvent>
    void subscribe(std::function<void(const TEvent &)> listener);

    template<typename TEvent>
    void dispatch(const TEvent &event);

    ~EventBus();

private:
    std::unordered_map<std::type_index, std::vector<std::function<void(const IEvent &)> > > listeners;
};
