#include "app_state__loading.h"

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

#include "app_state__game.h"

LoadingAppState LoadingAppState::playState;

LoadingAppState::LoadingAppState() :
    m_app(nullptr),
    m_opts(nullptr),
    m_sceneSystem(nullptr),
    m_sysManager(nullptr)
{}

void LoadingAppState::init(App& app)
{
    m_app = &app;
    m_opts = &app.m_opts;
    
    app.m_resSystem->initGame();

    // TODO: rework
    m_sceneSystem = app.m_sceneSystem.get();
    m_sysManager = app.m_gameSysManager.get();
    m_sceneSystem->init(*m_sysManager, *app.m_resSystem);
    
    m_sceneSystem->load("");
    /*Json saveNode;
    std::ifstream saveFile("save.json");
    saveFile >> saveNode;
    saveFile.close();

    m_sceneSystem->load(saveNode.at("scene_mgr"), *m_app->m_resSystem);
    IDManager::instance().load(saveNode.at("id_manager"));*/

    m_sysManager->init(*app.m_inputSubsystem, *app.m_rendSubsystem, *app.m_resSystem, *m_sceneSystem);
    // TODO: update when C++17 support will be better
    for (auto pair : m_sceneSystem->getScene()->getIDToActorMap())
    {
        auto actor = pair.second;
        m_sysManager->reg(*actor);
    }

    m_app->m_gameGUI.reset(new gui::GameGUI());
    m_app->m_gameGUI->init(*m_opts, 
                           *app.m_rendSubsystem, 
                           *m_app->m_gameSysManager, 
                           *m_app->m_sceneSystem, 
                           *m_app->m_resSystem);

    m_app->changeState(*GameAppState::instance());
}

void LoadingAppState::clean()
{
}

void LoadingAppState::pause()
{}

void LoadingAppState::resume()
{}

void LoadingAppState::handle()
{
    m_app->m_inputSubsystem->update();
}

void LoadingAppState::update()
{}

void LoadingAppState::render()
{
    m_app->m_rendSubsystem->clear();
    m_app->m_rendSubsystem->renderPresent();
}

LoadingAppState* LoadingAppState::instance()
{
    return &playState;
}
