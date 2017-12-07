#include "system_manager.h"

#include "game_sheduler.h"
#include "resource_manager.h"

#include "subsystem_input.h"

#include "control_sheduler.h"

SystemManager::SystemManager() :
    m_gameSheduler(new Sheduler()),
    m_sceneManager(nullptr),
    m_lootSystem(new LootSystem()),
    m_controlSheduler(new ControlSheduler()),
    m_viewSystem(new ViewSystem()),
    m_statsSystem(new StatsSystem()), 
    m_resManager(nullptr)
{}

bool SystemManager::init(ResourceManager& resManager, InputSubsystem& inputSubsystem, RenderSubsystem& rendSubsystem, SceneManager& sceneManager)
{
    m_resManager = &resManager;
    m_sceneManager = &sceneManager;

    m_gameSheduler->init();
    m_lootSystem->init(*this, sceneManager);
    m_statsSystem->init(*this);
    m_controlSheduler->init(inputSubsystem, sceneManager, *this);
    m_viewSystem->init(rendSubsystem, resManager, *this, sceneManager);

    m_systems.push_back(m_controlSheduler);
    m_systems.push_back(m_lootSystem);
    m_systems.push_back(m_viewSystem);
    m_systems.push_back(m_statsSystem);
    return true;
}

void SystemManager::reg(Actor& actor)
{
    for (auto system : m_systems)
    {
        system->reg(actor);
    }
}

void SystemManager::unreg(ActorID id)
{
    for (auto system : m_systems)
    {
        system->unreg(id);
    }
}

void SystemManager::update()
{
    m_viewSystem->update();
    //m_controller->update();
}

SystemManager::~SystemManager()
{
    for (auto& system : m_systems)
    {
        delete(system);
    }
}

