#pragma once

#include <string>

#include "event.h"

class LoadEvent : public Event
{
public:
    explicit LoadEvent(std::string profile, 
                       std::string save, 
                       Object* sender = nullptr) :
        Event(sender),
        m_profile(std::move(profile)),
        m_save(std::move(save))
    {}

    virtual ~LoadEvent() = default;

private:
    std::string m_profile;
    std::string m_save;

    friend class LoadingAppState;
};