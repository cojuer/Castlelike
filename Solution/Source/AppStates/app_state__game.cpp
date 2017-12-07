#include "app_state__game.h"

#include "game_gui.h"
#include "scene.h"
#include "control_sheduler.h"
#include "event_bus.h"
#include "resource_manager.h"
#include "scene_manager.h"
#include "system_manager.h"
#include "game_sheduler.h"

#include "subsystem_input.h"
#include "subsystem_render.h"

#include "listener__gui.h"
// TEST
#include "dialmanager.h"
#include "global_time.h"

GameAppState GameAppState::playState;

GameAppState::GameAppState() :
    m_app(nullptr),
    m_opts(nullptr), 
    m_sceneManager(nullptr), 
    m_sysManager(nullptr)
{}

void GameAppState::init(App& app)
{
    m_app = &app;
    m_opts = &app.m_opts;
    app.m_resManager->initGame();

    // TODO: rework
    m_sceneManager = app.m_sceneManager.get();
    m_sysManager = app.m_sysManager.get();
    m_sceneManager->init(*m_sysManager, *app.m_resManager);
    m_sceneManager->load("");

    m_sysManager->init(*app.m_resManager, *app.m_inputSubsystem, *app.m_rendSubsystem, *m_sceneManager);
    for (auto&[id, actor] : m_sceneManager->getScene()->getIDToActorMap())
    {
        m_sysManager->reg(*actor);
    }

    m_app->m_gameGUI.reset(new gui::GameGUI());
    m_app->m_gameGUI->init(*m_opts, *app.m_rendSubsystem, *m_app->m_sysManager, *m_app->m_sceneManager, *m_app->m_resManager);
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
    if (!m_app->m_sysManager->m_gameSheduler->isSheduleEmpty())
    {
        m_app->m_sysManager->m_gameSheduler->refresh();
    }
    else
    {
        m_app->m_sysManager->m_controlSheduler->update();
    }
    m_app->m_sysManager->m_lootSystem->update();
    m_app->m_sysManager->m_statsSystem->update();
}

void GameAppState::render()
{
    m_app->m_rendSubsystem->clear();
    m_app->m_sysManager->m_viewSystem->update();
    m_app->m_gameGUI->render();
    m_app->m_rendSubsystem->renderPresent();
}

GameAppState* GameAppState::instance()
{
    return &playState;
}