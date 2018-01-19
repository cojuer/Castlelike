#pragma once

#include <map>

#include "id_manager.h"
#include "controller.h"

class SceneSystem;
class InputSubsystem;
class GameSystemManager;

class PlayerController : public Controller
{
public:
    PlayerController() = default;

    bool init(SceneSystem& sceneSystem, InputSubsystem& inputSubsystem, GameSystemManager& sysManager);

    bool possess(Actor& actor) override;
    bool control(Actor& actor) override;

    std::map<ActorID, Actor*>& getPossessed();

private:
    SceneSystem*             m_sceneSystem;
    InputSubsystem*           m_inputSubsystem;
    GameSystemManager*            m_sysManager;
    Direction                 m_heroDir;
    std::map<ActorID, Actor*> m_registered;
};