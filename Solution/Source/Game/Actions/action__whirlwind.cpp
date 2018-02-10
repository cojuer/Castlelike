#include "action__whirlwind.h"

#include "scene.h"
#include "vec2.h"
#include "rng.h"

#include "component__attr.h"
#include "component__mdfr.h"
#include "component__health.h"
#include "component__experience_interface.h"
#include "event__journal.h"
#include "subsystem__event.h"

#include "utils.h"

WhirlwindAction::WhirlwindAction(ActionArgs&& args) :
    AttackAction(std::move(args))
{}

std::vector<std::string> WhirlwindAction::getRequiredArgTypes() const
{
    std::vector<std::string> allArgTypesNeeded = {
        ActArgType::user,
        ActArgType::scene
    };
    std::vector<std::string> argTypesNeeded;
    for (auto& type : allArgTypesNeeded)
    {
        if (m_args.find(type) == m_args.end())
        {
            argTypesNeeded.push_back(type);
        }
    }
    return argTypesNeeded;
}

bool WhirlwindAction::canAct() const
{
    return getRequiredArgTypes().empty();
}

std::vector<Actor*> WhirlwindAction::getVictims() const
{
    auto& attacker = *get<Actor*>(m_args, ActArgType::user);
    auto& scene = *get<Scene*>(m_args, ActArgType::scene);

    auto coord = attacker.getCoord();
    std::vector<Coord> tgtCoords = {
        { coord.x - 1, coord.y - 1 }, { coord.x, coord.y - 1 }, { coord.x + 1, coord.y - 1 },
        { coord.x - 1, coord.y }, { coord.x + 1, coord.y },
        { coord.x - 1, coord.y + 1 },{ coord.x, coord.y + 1 },{ coord.x + 1, coord.y + 1 }
    };
    std::vector<Actor*> victims;
    for (auto& tgtCoord : tgtCoords)
    {
        for (auto actor : scene.getActorsAtCoord(tgtCoord))
        {
            auto hpComp = actor->getComponent<HealthComponent>();
            bool actorOk = hpComp;
            if (actorOk)
            {
                victims.push_back(actor);
            }
        }
    }
    return victims;
}
