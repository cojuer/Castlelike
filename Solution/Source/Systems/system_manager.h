#pragma once

#include "system__loot.h"
#include "system__stats.h"
#include "system__view.h"

class Actor;
class ControlSheduler;
class InputSubsystem;
class SceneManager;
class Sheduler;

class SystemManager
{
public:
    SystemManager();
    SystemManager(const SystemManager&) = delete;
    SystemManager& operator=(const SystemManager&) = delete;

    bool init(ResourceManager& resManager, InputSubsystem& inputSubsystem, RenderSubsystem& rendSubsystem, SceneManager& sceneManager);

    void reg(Actor& actor);
    void unreg(ActorID id);

    void update();

    Sheduler*        m_gameSheduler;
    SceneManager*    m_sceneManager;
    LootSystem*      m_lootSystem;
    ControlSheduler* m_controlSheduler;
    ViewSystem*      m_viewSystem;
    StatsSystem*     m_statsSystem;

    ~SystemManager();

private:
    std::vector<System*> m_systems;

    ResourceManager*  m_resManager;
};
