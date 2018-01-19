#pragma once

#include <map>
#include <vector>

#include "factions.h"

class Actor;
class Scene;

class Behaviour
{
    using ActorVec = std::vector<Actor*>;

public:
    Behaviour(FactionsMgr& mgr, Factions&& factions);

    /* faction relations stuff */
    int getRelation(Actor& actor);

    bool isAfraidOf(Actor& actor);
    bool isEnemyTo(Actor& actor);
    bool isNeutralTo(Actor& actor);
    bool isAllyTo(Actor& actor);

    /* decision making staff */
    void scanScene(Scene& scene);
    void makeMove();

    void react(std::string event);

    const Factions& getFactions() const;

private:
    Actor*       parent;
    Factions     factions;
    Relations    relations;
    ActorVec     enemies;
    ActorVec     allies;
    FactionsMgr* mgr;
};