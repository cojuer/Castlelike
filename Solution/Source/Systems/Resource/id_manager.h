#pragma once

#include <list>

#include "actor.h"

class IDManager
{
public:
    IDManager();

    ActorID getActorID();
    void    free(ActorID id);

    void    load(Json& node);
    Json    save() const;

    static IDManager& instance();

private:
    ActorID            m_current;
    std::list<ActorID> m_freed;
};