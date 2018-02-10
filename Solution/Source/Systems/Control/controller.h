#pragma once

class Actor;

class Controller
{
public:
    Controller() = default;

    Controller(const Controller&) = default;
    Controller(Controller&&) = default;
    Controller& operator=(const Controller&) = default;
    Controller& operator=(Controller&&) = default;

    virtual ~Controller() = default;

    virtual bool possess(Actor& actor) = 0;
    virtual void release(ActorID actorID) = 0;
    virtual bool control(Actor& actor) = 0;
};
