#pragma once

class Actor;

class Controller
{
public:
    virtual ~Controller() = default;
    virtual bool possess(Actor& actor) = 0;
    virtual void release(ActorID actorID) = 0;
    virtual bool control(Actor& actor) = 0;
};
