#include "app_state__loading.h"

#include "subsystem__input.h"
#include "subsystem__render.h"
#include "subsystem__rng.h"
#include "system__resource.h"
#include "system__save.h"
#include "system__scene.h"
#include "game_system_manager.h"

#include "app_state__game.h"
#include "id_manager.h"
#include "game_gui.h"


LoadingAppState LoadingAppState::playState;

LoadingAppState::LoadingAppState() :
    m_app(nullptr)
{}

void LoadingAppState::init(App& app)
{
    m_app = &app;
    
    m_app->m_resSystem->initGame();

    m_app->m_sceneSystem->init(*m_app->m_resSystem);
    
    m_app->m_saveSystem->regSerializable(*m_app->m_rngHolder);
    m_app->m_saveSystem->regSerializable(IDManager::instance());
    m_app->m_saveSystem->regSerializable(*m_app->m_sceneSystem);
    
    m_app->m_saveSystem->useProfile("test");
    m_app->m_sceneSystem->load("");
    //m_app->m_saveSystem->loadLast(*m_app->m_resSystem);

    m_app->m_gameSysManager->init(*m_app->m_inputSubsystem, 
                                  *m_app->m_rendSubsystem, 
                                  *m_app->m_resSystem, 
                                  *m_app->m_sceneSystem);
    // TODO: update when C++17 support will be better
    for (auto pair : m_app->m_sceneSystem->getScene()->getIDToActorMap())
    {
        auto actor = pair.second;
        m_app->m_gameSysManager->reg(*actor);
    }

    m_app->m_gameGUI.reset(new gui::GameGUI());
    m_app->m_gameGUI->init(m_app->m_opts,
                           *m_app->m_rendSubsystem,
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
