#pragma once

#include <set>
#include <vector>

#include "system.h"

class SceneManager;
class InputSubsystem;
class AIController;
class Controller;
class PlayerController;
class SystemManager;

class ControlSheduler : public System
{
public:
    ControlSheduler() = default;

    bool init(InputSubsystem& inputSubsystem, SceneManager& sceneManager, SystemManager& sysManager);

    bool reg(Actor& actor) override;
    void unreg(ActorID id) override;

    void update() override;

    ActorID getCurrentID();

    AIController*            m_aiController;
    PlayerController*        m_plController;

private:
    SystemManager*           m_sysManager;
    std::vector<std::pair<size_t, Actor*>> m_possessed;
    size_t                   m_current;
    bool                     m_giveAP;
    std::set<ActorID>        m_registered;
    std::vector<Controller*> m_controllers;

};