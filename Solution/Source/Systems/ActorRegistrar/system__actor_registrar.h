#pragma once

#include "system__loot.h"
#include "system__stats.h"

class Actor;
class ControlGSystem;
class InputSubsystem;
class SceneSystem;
class SheduleSystem;

class ActorRegistrar final
{
public:
    ActorRegistrar() = default;

    void addActorHolder(ActorHolder& reg);

    void reg(Actor& actor);
    void unreg(ActorID id);

private:
    std::vector<ActorHolder*> m_systems;
};
