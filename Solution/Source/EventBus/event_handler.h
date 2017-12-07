#pragma once

#include <type_traits>

class Event;

template <class T>
class EventHandler {
public:
    EventHandler() 
    {
        static_assert(std::is_base_of<Event, T>::value, "EventHandler<T>: T must be a class derived from Event");
    }

    virtual ~EventHandler() {}

    virtual void onEvent(T &) = 0;

    void dispatch(Event & e) 
    {
        onEvent(dynamic_cast<T &>(e));
    }
};