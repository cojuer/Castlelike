#include "player_controller.h"

#include "actor.h"
#include "scene.h"
#include "actions.h"
#include "action__attack.h"
#include "action__move.h"

#include "subsystem__input.h"

#include "game_system_manager.h"
#include "system__scene.h"

#include "component__health.h"
#include "component__player.h"

#include "event__shedule.h"
#include "subsystem__event.h"

#include "cutscene__attack.h"
#include "cutscene__move.h"
#include "component__action_pts.h"

bool PlayerController::init(SceneSystem& sceneSystem, InputSubsystem& inputSubsystem, GameSystemManager& sysManager)
{
    m_sceneSystem = &sceneSystem;
    m_inputSubsystem = &inputSubsystem;
    m_heroDir = Direction::NONE;
    m_sysManager = &sysManager;
    return true;
}

bool PlayerController::possess(Actor& actor)
{
    auto plComponent = actor.getComponent<PlayerComponent>();
    if (plComponent)
    {
        m_registered.insert(std::make_pair(actor.getID(), &actor));
        return true;
    }
    return false;
}

void PlayerController::release(ActorID actorID)
{
    m_registered.erase(actorID);
}

bool PlayerController::control(Actor& actor)
{
    // If no AP, turn is over
    auto apComp = actor.getComponent<ActionPtsComponent>();
    if (apComp->getCurr() == 0)
    {
        return true;
    }

    auto& events = m_inputSubsystem->getEvents();
    for (auto& event: events)
    {
        if (event.type == SDL_KEYDOWN)
        {
            auto curr = event.key.keysym.sym;
            switch(curr)
            {
            case SDLK_w: m_heroDir = Direction::UPWARD; break;
            case SDLK_s: m_heroDir = Direction::DOWNWARD; break;
            case SDLK_a: m_heroDir = Direction::LEFTWARD; break;
            case SDLK_d: m_heroDir = Direction::RIGHTWARD; break;
            default: break;
            }
        }
    }
    if (m_heroDir != Direction::NONE)
    {
        auto hero = &actor;
        auto scene = m_sceneSystem->getScene();
        auto coord = Coord(m_heroDir) + hero->getCoord();
        if (scene->isEmpty(coord))
        {
            ActionArgs input;
            input[ActArgType::coord] = new Coord(coord);
            input[ActArgType::user] = hero;
            input[ActArgType::scene] = scene;

            auto cutscene = new MoveCutscene(*hero, Coord(m_heroDir), TimeUnit::ms(100));
            SheduleEvent cutsceneEvent{ cutscene };
            EventSubsystem::FireEvent(cutsceneEvent);

            auto action = new MoveAction{ std::move(input) };
            SheduleEvent actionEvent{ action };
            EventSubsystem::FireEvent(actionEvent);
        }
        else 
        {
            for (auto target : scene->getActorsAtCoord(coord))
            {
                if (target->getComponent<HealthComponent>())
                {
                    ActionArgs input;
                    input[ActArgType::coord] = new Coord(coord);
                    input[ActArgType::user] = hero;
                    input[ActArgType::scene] = scene;

                    Coord shift{ m_heroDir };
                    auto cutscene = new AttackCutscene(actor, shift, TimeUnit::ms(200));
                    SheduleEvent cutsceneEvent{ cutscene };
                    EventSubsystem::FireEvent(cutsceneEvent);

                    auto action = new AttackAction{ std::move(input) };
                    SheduleEvent actionEvent{ action };
                    EventSubsystem::FireEvent(actionEvent);
                }
            }
        }
        m_heroDir = Direction::NONE;
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

std::map<ActorID, Actor*>& PlayerController::getPossessed()
{
    return m_registered;
}
