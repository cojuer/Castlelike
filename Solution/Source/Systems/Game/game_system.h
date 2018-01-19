#pragma once

#include "actor.h"

class GameSystem
{
public:
    virtual bool reg(Actor& actor) = 0;
    virtual void unreg(ActorID id) = 0;

    virtual void update() = 0;

    virtual ~GameSystem() = default;
};