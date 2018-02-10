#pragma once

#include <map>

#include "system__actor_id.h"
#include "controller.h"

class SceneSystem;
class InputSubsystem;
class ActorRegistrar;

class PlayerController : public Controller
{
public:
    PlayerController() = default;

    bool init(SceneSystem& sceneSystem, InputSubsystem& inputSubsystem);

    bool possess(Actor& actor) override;
    void release(ActorID actorID) override;
    bool control(Actor& actor) override;

    std::map<ActorID, Actor*>& getPossessed();

private:
    SceneSystem*              m_sceneSystem { nullptr };
    InputSubsystem*           m_inputSubsystem { nullptr };
    Direction                 m_heroDir { Direction::NONE };
    std::map<ActorID, Actor*> m_registered;
};