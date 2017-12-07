#pragma once

#include "event.h"
#include "event_type__actor.h"
#include "actor.h"

class ActorEvent : public Event
{
public:
    ActorEvent(ActorEvType type, ActorID id, Object* sender = nullptr) :
        Event(sender),
        m_type(type),
        m_actorID(id)
    {}

    ActorEvType      m_type;
    ActorID          m_actorID;
};
