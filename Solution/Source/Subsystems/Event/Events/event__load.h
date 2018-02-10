#pragma once

#include <string>

#include "event.h"

class LoadEvent final : public Event
{
public:
    explicit LoadEvent(std::string profile, 
                       std::string save, 
                       Object* sender = nullptr) :
        Event(sender),
        m_profile(std::move(profile)),
        m_save(std::move(save))
    {}

private:
    std::string m_profile;
    std::string m_save;

    friend class LoadingAppState;
};