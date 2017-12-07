#pragma once

#include "actor.h"

class Container;

class StorageActor : public Actor
{
public:
    StorageActor(ActorID id, Coord pos, const std::string& resID, bool collisive, Container& container, bool solid);

    Container& getContainer() const;
};
