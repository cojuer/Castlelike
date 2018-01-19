#include "game_system_manager.h"

#include "system__shedule.h"
#include "system__resource.h"

#include "subsystem_input.h"

#include "control_sheduler.h"

GameSystemManager::GameSystemManager() :
    m_sheduleSystem(new SheduleSystem()),
    m_sceneSystem(nullptr),
    m_lootSystem(new LootGSystem()),
    m_controlSheduler(new ControlGSystem()),
    m_viewSystem(new ViewSystem()),
    m_statsSystem(new StatsGSystem()), 
    m_resSystem(nullptr)
{}

bool GameSystemManager::init(InputSubsystem& inputSubsystem, RenderSubsystem& rendSubsystem, ResourceSystem& resSystem, SceneSystem& sceneSystem)
{
    m_resSystem = &resSystem;
    m_sceneSystem = &sceneSystem;

    m_sheduleSystem->init();
    m_lootSystem->init(*this, sceneSystem);
    m_statsSystem->init(*this);
    m_controlSheduler->init(inputSubsystem, sceneSystem, *this);
    m_viewSystem->init(rendSubsystem, resSystem, *this, sceneSystem);

    m_systems.push_back(m_controlSheduler);
    m_systems.push_back(m_lootSystem);
    m_systems.push_back(m_viewSystem);
    m_systems.push_back(m_statsSystem);
    return true;
}

void GameSystemManager::reg(Actor& actor)
{
    for (auto system : m_systems)
    {
        system->reg(actor);
    }
}

void GameSystemManager::unreg(ActorID id)
{
    for (auto system : m_systems)
    {
        system->unreg(id);
    }
}

void GameSystemManager::update()
{
    m_viewSystem->update();
    //m_controller->update();
}

GameSystemManager::~GameSystemManager()
{
    for (auto& system : m_systems)
    {
        delete(system);
    }
}

