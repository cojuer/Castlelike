#pragma once

#include "actor.h"

class Container;

class Door : public Actor
{
public:
	Door(ActorID id, Coord pos, const std::string& resID, bool collisive);
};
