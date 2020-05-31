#include "ai_controller.h"

#include <iostream>

#include "actor.h"
#include "scene.h"
#include "system__scene.h"
#include "component__ai.h"
#include "utils.h"
#include "actions.h"
#include "action__attack.h"
#include "action__move.h"
#include "pathfinding.h"
#include "component__health.h"

#include "event__shedule.h"
#include "subsystem__event.h"

#include "cutscene__attack.h"
#include "cutscene__move.h"
#include "component__action_pts.h"

bool AIController::init(SceneSystem& sceneSystem)
{
    m_sceneSystem = &sceneSystem;
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

void AIController::release(ActorID actorID)
{
    m_registered.erase(actorID);
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

    auto& scene = *m_sceneSystem->getScene();

    auto coord = possessed.getCoord();

    auto& hero = *scene.getHero();
    std::vector<Actor*> targets;
    /* any logic for finding targets can be implemented here */
    if (utils::coordDist(coord, hero.getCoord()) <= 3) 
    {
        targets.push_back(&hero);
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
            // FIXME: memory leak
            input[ActArgType::coord] = Coord(target->getCoord());
            input[ActArgType::user] = &possessed;
            input[ActArgType::scene] = &scene;

            Coord shift{ target->getCoord() - possessed.getCoord() };
            auto cutscene = new AttackCutscene(possessed, shift, TimeUnit::ms(200));
            SheduleEvent cutsceneEvent{ cutscene, nullptr };
            EventSubsystem::FireEvent(cutsceneEvent);

            auto action = new AttackAction{ std::move(input) };
            SheduleEvent actionEvent{ action, nullptr };
            EventSubsystem::FireEvent(actionEvent);

            std::cout << "ai: attack" << std::endl;
        }
        else
        {
            auto path = ai::AStarAlgorithm::findPath(scene, possessed.getCoord(), target->getCoord());
            if (!path.empty())
            {
                ActionArgs input;
                input[ActArgType::coord] = path.front();
                input[ActArgType::user] = &possessed;
                input[ActArgType::scene] = &scene;

                Coord shift{ path.front() - possessed.getCoord() };
                auto cutscene = new MoveCutscene(possessed, shift, TimeUnit::ms(100));
                SheduleEvent cutsceneEvent{ cutscene, nullptr };
                EventSubsystem::FireEvent(cutsceneEvent);

                auto action = new MoveAction{ std::move(input) };
                SheduleEvent actionEvent{ action, nullptr };
                EventSubsystem::FireEvent(actionEvent);
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
    return (apComp->getCurr() == 0);
}
