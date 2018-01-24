#pragma once

#include <map>

#include "system__actor_id.h"
#include "controller.h"

class SceneSystem;
class GameSystemManager;

class AIController : public Controller
{
public:
    AIController() = default;

    bool init(SceneSystem& sceneSystem, GameSystemManager& sysManager);

    bool possess(Actor& actor) override;
    void release(ActorID actorID) override;

    bool control(Actor& actor) override;

private:
    SceneSystem*             m_sceneSystem;
    GameSystemManager*            m_sysManager;
    std::map<ActorID, Actor*> m_registered;
};