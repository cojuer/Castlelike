#include "action__move.h"

#include <iostream>

#include "scene.h"
#include "vec2.h"

#include "component__reactor.h"
#include "component__action_pts.h"

MoveAction::MoveAction(ActionArgs&& args) :
    m_args(std::move(args))
{}

void MoveAction::act()
{
    auto& user = *get<Actor*>(m_args, ActArgType::user);
    auto& scene = *get<Scene*>(m_args, ActArgType::scene);
    auto& coord = *get<Coord*>(m_args, ActArgType::coord);

    if (scene.isEmpty(coord))
    {
        scene.relocateActor(user, coord);
        auto reactor = user.getComponent<ReactorComponent>();
        if (reactor)
        {
            ActionArgs reactInput{ { "src", user.getCoord() },{ "dst", coord } };
            reactor->react("move", reactInput);
        }
    }

    auto actPtsComp = user.getComponent<ActionPtsComponent>();
    if (actPtsComp)
    {
        actPtsComp->setCurr(actPtsComp->getCurr() - 1);
    }
}

void MoveAction::setArg(std::string argType, std::any arg)
{
    m_args[argType] = arg;
}

std::vector<std::string> MoveAction::getRequiredArgTypes() const
{
    std::vector<std::string> allArgTypesNeeded = {
        ActArgType::user,
        ActArgType::scene,
        ActArgType::coord
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

bool MoveAction::canAct() const
{
    if (getRequiredArgTypes().size() == 0)
    {
        return true;
    }
    return false;
}