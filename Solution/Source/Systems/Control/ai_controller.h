#pragma once

#include <map>

#include "system__actor_id.h"
#include "controller.h"

class SceneSystem;
class ActorRegistrar;

class AIController : public Controller
{
public:
    AIController() = default;

    bool init(SceneSystem& sceneSystem);

    bool possess(Actor& actor) override;
    void release(ActorID actorID) override;

    bool control(Actor& possessed) override;

private:
    SceneSystem*              m_sceneSystem { nullptr };
    std::map<ActorID, Actor*> m_registered;
};