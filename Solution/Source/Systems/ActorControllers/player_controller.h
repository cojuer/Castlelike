#pragma once

#include <map>

#include "id_manager.h"
#include "controller.h"

class SceneManager;
class InputSubsystem;
class SystemManager;

class PlayerController : public Controller
{
public:
    PlayerController() = default;

    bool init(SceneManager& sceneManager, InputSubsystem& inputSubsystem, SystemManager& sysManager);

    bool possess(Actor& actor) override;
    bool control(Actor& actor) override;

    std::map<ActorID, Actor*>& getPossessed();

private:
    SceneManager*             m_sceneManager;
    InputSubsystem*           m_inputSubsystem;
    SystemManager*            m_sysManager;
    Direction                 m_heroDir;
    std::map<ActorID, Actor*> m_registered;
};