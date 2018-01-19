#pragma once

#include <set>
#include <vector>

#include "game_system.h"

class SceneSystem;
class InputSubsystem;
class AIController;
class Controller;
class PlayerController;
class GameSystemManager;

class ControlGSystem : public GameSystem
{
public:
    ControlGSystem() = default;

    bool init(InputSubsystem& inputSubsystem, SceneSystem& sceneSystem, GameSystemManager& sysManager);

    bool reg(Actor& actor) override;
    void unreg(ActorID id) override;

    void update() override;

    ActorID getCurrentID();

    AIController*            m_aiController;
    PlayerController*        m_plController;

private:
    GameSystemManager*           m_sysManager;
    std::vector<std::pair<size_t, Actor*>> m_possessed;
    size_t                   m_current;
    bool                     m_giveAP;
    std::set<ActorID>        m_registered;
    std::vector<Controller*> m_controllers;

};