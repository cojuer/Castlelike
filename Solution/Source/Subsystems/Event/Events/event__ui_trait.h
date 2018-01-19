#pragma once

#include "event.h"

class UI_TraitEvent : public Event
{
public:
    UI_TraitEvent(std::string trait, Object* sender = nullptr) :
        Event(sender),
        trait(trait)
    {}

    virtual ~UI_TraitEvent() {};

    std::string trait;
};
