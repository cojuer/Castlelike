#pragma once

#include "game_system__loot.h"
#include "game_system__stats.h"
#include "system__view.h"

class Actor;
class ControlGSystem;
class InputSubsystem;
class SceneSystem;
class SheduleSystem;

class GameSystemManager final
{
public:
    GameSystemManager();
    GameSystemManager(const GameSystemManager&) = delete;
    GameSystemManager(const GameSystemManager&&) = delete;
    GameSystemManager& operator=(const GameSystemManager&) = delete;
    GameSystemManager& operator=(const GameSystemManager&&) = delete;

    bool init(InputSubsystem& inputSubsystem, 
              RenderSubsystem& rendSubsystem, 
              ResourceSystem& resSystem, 
              SceneSystem& sceneSystem);

    void reg(Actor& actor);
    void unreg(ActorID id);

    void update();
    void clean();

    SheduleSystem*   m_sheduleSystem;
    SceneSystem*     m_sceneSystem;
    ViewSystem*      m_viewSystem;

    LootGSystem*      m_lootSystem;
    ControlGSystem*   m_controlSheduler;
    StatsGSystem*     m_statsSystem;

    ~GameSystemManager();

private:
    std::vector<GameSystem*> m_systems;

    ResourceSystem*  m_resSystem;
};
