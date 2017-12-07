#include "ai_controller.h"

#include <iostream>

#include "actor.h"
#include "scene.h"
#include "scene_manager.h"
#include "component__ai.h"
#include "utils.h"
#include "actions.h"
#include "action__attack.h"
#include "action__move.h"
#include "pathfinding.h"
#include "system_manager.h"
#include "component__health.h"

#include "event__shedule.h"
#include "event_bus.h"

#include "cutscene__attack.h"
#include "cutscene__move.h"
#include "component__action_pts.h"

bool AIController::init(SceneManager& sceneManager, SystemManager& sysManager)
{
    m_sceneManager = &sceneManager;
    m_sysManager = &sysManager;
    return true;
}

bool AIController::possess(Actor& actor)
{
    auto aiComponent = actor.getComponent<AIComponent>();
    if (aiComponent && aiComponent->possess())
    {
        m_registered.insert(std::make_pair(actor.getID(), &actor));
        return true;
    }
    return false;
}

bool AIController::control(Actor& possessed)
{
    // FIXME: ???
    if (m_registered.find(possessed.getID()) == m_registered.end()) return true;

    // If no AP, turn is over
    auto apComp = possessed.getComponent<ActionPtsComponent>();
    if (apComp->getCurr() == 0)
    {
        return true;
    }

    auto& scene = *m_sceneManager->getScene();

    auto coord = possessed.getCoord();

    std::vector<Actor*> targets;
    for (auto x = coord.x - 4; x <= coord.x + 4; ++x)
    {
        for (auto y = coord.y - 4; y <= coord.y + 4; ++y)
        {
            if (scene.getTile({x, y}))
            {
                auto actors = scene.getActorsAtCoord({ x, y });
                for (auto actor : actors)
                {
                    if (actor->getID() != possessed.getID() &&
                        actor->getComponent<HealthComponent>())
                    {
                        targets.push_back(actor);
                    }
                }
            }
        }
    }
    Actor* target = nullptr;
    int minRange = 10;
    for (auto& actor : targets)
    {
        if (utils::coordDist(coord, actor->getCoord()) <= minRange)
        {
            minRange = utils::coordDist(coord, actor->getCoord());
            target = actor;
        }
    }
    if (target)
    {
        auto dist = utils::coordDist(possessed.getCoord(), target->getCoord());

        if (dist == 1)
        {
            ActionArgs input;
            // FIXME: coord by value?
            input[ActArgType::coord] = new Coord(target->getCoord());
            input[ActArgType::user] = &possessed;
            input[ActArgType::scene] = &scene;

            Coord shift{ target->getCoord() - possessed.getCoord() };
            auto cutscene = new AttackCutscene(possessed, shift, TimeUnit::ms(200));
            SheduleEvent cutsceneEvent{ cutscene, nullptr };
            EventBus::FireEvent(cutsceneEvent);

            auto action = new AttackAction{ std::move(input) };
            SheduleEvent actionEvent{ action, nullptr };
            EventBus::FireEvent(actionEvent);

            std::cout << "ai: attack" << std::endl;
        }
        else
        {
            auto path = ai::AStarAlgorithm::findPath(scene, possessed.getCoord(), target->getCoord());
            if (path.size() > 0)
            {
                ActionArgs input;
                input[ActArgType::coord] = new Coord(path.front());
                input[ActArgType::user] = &possessed;
                input[ActArgType::scene] = &scene;

                Coord shift{ path.front() - possessed.getCoord() };
                auto cutscene = new MoveCutscene(possessed, shift, TimeUnit::ms(100));
                SheduleEvent cutsceneEvent{ cutscene, nullptr };
                EventBus::FireEvent(cutsceneEvent);

                auto action = new MoveAction{ std::move(input) };
                SheduleEvent actionEvent{ action, nullptr };
                EventBus::FireEvent(actionEvent);
            }
            else
            {
                // Path not found.
                return true;
            }
            std::cout << "ai: move to target" << std::endl;
        }
    }
    else
    {
        // If no target, NPC is sleeping.
        return true;
    }
    
    // If no AP, turn is over
    if (apComp->getCurr() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
