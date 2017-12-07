#include "action__swing.h"

#include "scene.h"
#include "vec2.h"

#include "component__health.h"

SwingAction::SwingAction(ActionArgs&& args) :
    AttackAction(std::move(args))
{}

std::vector<Actor*> SwingAction::getVictims() const
{
    auto& attacker = *get<Actor*>(m_args, ActArgType::user);
    auto& scene = *get<Scene*>(m_args, ActArgType::scene);
    auto& coord = *get<Coord*>(m_args, ActArgType::coord);

    auto userCoord = attacker.getCoord();
    std::vector<Actor*> victims;
    std::vector<Coord> tgtCoords;
    if (userCoord.x != coord.x)
    {
        tgtCoords = {
            { coord.x, coord.y - 1 },
            { coord.x, coord.y },
            { coord.x, coord.y + 1 }
        };
    }
    else if(userCoord.y != coord.y)
    {
        tgtCoords = {
            { coord.x - 1, coord.y },
            { coord.x, coord.y },
            { coord.x + 1, coord.y }
        };
    }
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
