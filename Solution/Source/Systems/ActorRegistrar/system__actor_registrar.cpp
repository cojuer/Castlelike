#include "system__actor_registrar.h"

void ActorRegistrar::addActorHolder(ActorHolder& reg)
{
    m_systems.push_back(&reg);
}

void ActorRegistrar::reg(Actor& actor)
{
    for (auto system : m_systems)
    {
        system->reg(actor);
    }
}

void ActorRegistrar::unreg(ActorID id)
{
    for (auto system : m_systems)
    {
        system->unreg(id);
    }
}

