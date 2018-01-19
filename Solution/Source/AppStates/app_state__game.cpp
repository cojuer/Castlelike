#include "app_state__game.h"

#include "game_gui.h"
#include "scene.h"
#include "control_sheduler.h"
#include "subsystem__event.h"
#include "system__resource.h"
#include "system__scene.h"
#include "game_system_manager.h"
#include "system__shedule.h"

#include "subsystem_input.h"
#include "subsystem_render.h"

#include "listener__gui.h"
// TEST
#include "dialmanager.h"
#include "global_time.h"
#include "rng_holder.h"
#include <fstream>
#include "id_manager.h"

GameAppState GameAppState::playState;

GameAppState::GameAppState() :
    m_app(nullptr),
    m_opts(nullptr), 
    m_sceneSystem(nullptr), 
    m_sysManager(nullptr)
{}

void GameAppState::init(App& app)
{
    m_app = &app;
    m_opts = &app.m_opts;

    // TODO: rework
    m_sceneSystem = app.m_sceneSystem.get();
    m_sysManager = app.m_gameSysManager.get();
}

void GameAppState::clean()
{
}

void GameAppState::pause()
{}

void GameAppState::resume()
{}

void GameAppState::handle()
{
    m_app->m_inputSubsystem->update();
    for (auto event : m_app->m_inputSubsystem->getEvents())
    {
        m_app->m_gameGUI->handle(event);
    }
}

void GameAppState::update()
{
    if (!m_app->m_gameSysManager->m_sheduleSystem->isSheduleEmpty())
    {
        m_app->m_gameSysManager->m_sheduleSystem->refresh();
    }
    else
    {
        m_app->m_gameSysManager->m_controlSheduler->update();
    }
    m_app->m_gameSysManager->m_lootSystem->update();
    m_app->m_gameSysManager->m_statsSystem->update();
}

void GameAppState::render()
{
    m_app->m_rendSubsystem->clear();
    m_app->m_gameSysManager->m_viewSystem->update();
    m_app->m_gameGUI->render();
    m_app->m_rendSubsystem->renderPresent();
}

GameAppState* GameAppState::instance()
{
    return &playState;
}

void GameAppState::save()
{
    Json result;
    result["scene_mgr"] = m_sceneSystem->save();
    result["rng_holder"] = m_app->m_rngHolder->save();
    result["id_manager"] = IDManager::instance().save();
    std::ofstream saveFile("save.json");
    saveFile << std::setw(4) << result;
    saveFile.close();
}
