#include "action__push.h"

#include "actor.h"
#include "action__move.h"
#include "scene.h"
#include "component__weight.h"

PushAction::PushAction(ActionArgs&& args) :
    m_args(std::move(args))
{}

void PushAction::act()
{
    auto& user = *get<Actor*>(m_args, ActArgType::user);
    auto& scene = *get<Scene*>(m_args, ActArgType::scene);
    auto coord = get<Coord>(m_args, ActArgType::coord);

    auto victims = getVictims(scene, coord);
    auto weightSum = 0;
    for (auto victim : victims)
    {
        auto weight = victim->getComponent<WeightComponent>()->getCurr();
        weightSum += weight;
    }

    pushActorOff(user, weightSum, coord, scene);
    
    auto userWeight = user.getComponent<WeightComponent>()->getCurr();
    for (auto victim : victims)
    {
        pushActorOff(*victim, userWeight, user.getCoord(), scene);
    }
}

void PushAction::setArg(std::string argType, std::any arg)
{
    m_args[argType] = arg;
}

std::vector<std::string> PushAction::getRequiredArgTypes() const
{
    std::vector<std::string> allArgTypesNeeded = {
        ActArgType::user,
        ActArgType::power
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

bool PushAction::canAct() const
{
    auto readyToAct = false;
    readyToAct = readyToAct && getRequiredArgTypes().empty();
    
    auto user = get<Actor*>(m_args, ActArgType::user);
    readyToAct = readyToAct && user;
    
    auto weightComp = user->getComponent<WeightComponent>();
    readyToAct = readyToAct && weightComp;
    
    return readyToAct;
}

std::vector<Actor*> PushAction::getVictims(Scene& scene, Coord coord) const
{
    std::vector<Actor*> victims;
    for (auto actor : scene.getActorsAtCoord(coord))
    {
        auto tgtWeightComp = actor->getComponent<WeightComponent>();
        if (tgtWeightComp)
        {
            victims.push_back(actor);
        }
    }
    return victims;
}

void PushAction::pushActorOff(Actor& actor, int weight, Coord weightCoord, Scene& scene)
{
    auto actorMoveDistance = 1;
    auto actorWeight = actor.getComponent<WeightComponent>()->getCurr();
    if (actorWeight > 2 * weight)
    {
        actorMoveDistance = 0;
    }
    else if (weight > 2 * actorWeight)
    {
        actorMoveDistance = 2;
    }

    Coord userCoordDiff{ 0, 0 };
    auto userBeforeCoord = actor.getCoord();
    if (userBeforeCoord.x != weightCoord.x)
    {
        userCoordDiff.x = (userBeforeCoord.x < weightCoord.x) ? -actorMoveDistance : actorMoveDistance;
    }
    if (userBeforeCoord.y != weightCoord.y)
    {
        userCoordDiff.y += (userBeforeCoord.y < weightCoord.y) ? -actorMoveDistance : actorMoveDistance;
    }

    auto userAfterCoord = userBeforeCoord + userCoordDiff;
    ActionArgs tgtArgs{ 
        { ActArgType::user, &actor },
        { ActArgType::scene, &scene },
        { ActArgType::coord, userAfterCoord } 
    };
    MoveAction tgtAction(std::move(tgtArgs));
    tgtAction.act();
}
