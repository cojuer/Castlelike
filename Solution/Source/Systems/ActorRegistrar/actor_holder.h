#pragma once

#include "actor.h"

class ActorHolder
{
public:
    ActorHolder() = default;

    ActorHolder(const ActorHolder&) = delete;
    ActorHolder(ActorHolder&&) = delete;
    ActorHolder& operator=(const ActorHolder&) = delete;
    ActorHolder& operator=(ActorHolder&&) = delete;

    virtual ~ActorHolder() = default;

    virtual bool reg(Actor& actor) = 0;
    virtual void unreg(ActorID id) = 0;
};