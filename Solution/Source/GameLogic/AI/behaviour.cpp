#include "AI/behaviour.h"

#include "utils.h"

Behaviour::Behaviour(FactionsMgr& mgr, Factions&& factions) : 
    parent(nullptr),
    factions(factions),
    mgr(&mgr)
{}

int Behaviour::getRelation(Actor& actor)
{
    // FIXME: rewrite for actors
    /*const auto& charFactions = actor.getBehaviour().getFactions();
    const auto& allRels = mgr->getRelations();

    auto activeRels = 0;
    auto relation = 0;
    for (auto& faction : factions)
    {
        for (auto& charFaction : charFactions)
        {
            auto iter = relations.find({ faction, charFaction });
            if (iter != relations.end())
            {
                relation += iter->second;
                ++activeRels;
            }
            auto seciter = allRels.find({ faction, charFaction });
            if (seciter != allRels.end())
            {
                relation += seciter->second;
                ++activeRels;
            }
        }
    }
    return relation / activeRels;*/
    return 0;
}

bool Behaviour::isAfraidOf(Actor& actor)
{
    auto rel = getRelation(actor);
    return (rel <= FactionsMgr::fearHBound);
}

bool Behaviour::isEnemyTo(Actor& actor)
{
    auto rel = getRelation(actor);
    return (rel >= FactionsMgr::hateLBound &&
            rel <= FactionsMgr::hateHBound);
}

bool Behaviour::isNeutralTo(Actor& actor)
{
    auto rel = getRelation(actor);
    return (rel >= FactionsMgr::neutralLBound &&
            rel <= FactionsMgr::neutralHBound);
}

bool Behaviour::isAllyTo(Actor& actor)
{
    auto rel = getRelation(actor);
    return (rel >= FactionsMgr::loveLBound);
}

const Factions& Behaviour::getFactions() const
{
    return factions;
}