#include "app_state__game.h"

#include "app_state__menu.h"
#include "app_state__loading.h"

#include "subsystem__input.h"
#include "subsystem__render.h"
#include "system__save.h"
#include "system__scene.h"
#include "system__shedule.h"
#include "game_system_manager.h"
#include "game_system__control.h"

#include "game_gui.h"

GameAppState GameAppState::playState;

GameAppState::GameAppState() :
    m_app(nullptr)
{}

void GameAppState::init(App& app)
{
    m_initialized = true;
    m_app = &app;
}

void GameAppState::clean()
{
    // TODO: update when C++17 support will be better
    for (auto pair : m_app->m_sceneSystem->getScene()->getIDToActorMap())
    {
        auto id = pair.first;
        m_app->m_gameSysManager->unreg(id);
    }
    m_app->m_sceneSystem->clean();
}

void GameAppState::start()
{}

void GameAppState::pause()
{}

void GameAppState::resume()
{}

void GameAppState::handle()
{
    m_app->m_inputSubsystem->update();
    for (auto event : m_app->m_inputSubsystem->getEvents())
    {
        if (event.type == SDL_KEYDOWN and event.key.keysym.sym == SDLK_F5)
        {
            // FIXME: use real values
            m_app->m_saveSystem->saveLast();
        }
        if (event.type == SDL_KEYDOWN and event.key.keysym.sym == SDLK_F9)
        {
            // FIXME: use real values
            m_app->changeState(*LoadingAppState::instance());
            return;
        }
        if (event.type == SDL_KEYDOWN and event.key.keysym.sym == SDLK_ESCAPE)
        {
            m_app->changeState(*MenuAppState::instance());
            return;
        }
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
