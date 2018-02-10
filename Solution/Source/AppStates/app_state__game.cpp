#include "app_state__game.h"

#include "app_state__menu.h"
#include "app_state__loading.h"

#include "subsystem__input.h"
#include "subsystem__render.h"
#include "system__actor_id.h"
#include "system__journal.h"
#include "system__save.h"
#include "system__scene.h"
#include "system__shedule.h"
#include "system__view.h"
#include "system__actor_registrar.h"
#include "system__control.h"

#include "game_gui.h"

GameAppState GameAppState::playState;

void GameAppState::init(App& app)
{
    m_initialized = true;
    m_app = &app;
}

void GameAppState::clean()
{
    m_app->m_gameGUI.reset();
    m_app->m_controlGSystem->clean();
    m_app->m_lootGSystem->clean();
    m_app->m_statsGSystem->clean();
    m_app->m_sceneSystem->clean();
    m_app->m_journalSystem->clean();
    m_app->m_viewSystem->clean();
    IDManager::instance().clean();
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
        // flag shows whether gui should be handled 
        auto handleFlag = true;
        if (event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_F5:
                m_app->m_saveSystem->saveLast();
                break;
            case SDLK_F9:
                m_app->m_loadSave = true;
                m_app->m_loadLast = true;
                m_app->changeState(*LoadingAppState::instance());
                handleFlag = false;
                break;
            case SDLK_ESCAPE:
                m_app->changeState(*MenuAppState::instance());
                handleFlag = false;
                break;
            default:
                break;
            }
        }
        if (handleFlag)
        {
            m_app->m_gameGUI->handle(event);
        }
    }
}

void GameAppState::update()
{
    if (!m_app->m_sheduleSystem->isSheduleEmpty())
    {
        m_app->m_sheduleSystem->refresh();
    }
    else
    {
        m_app->m_controlGSystem->update();
    }
    m_app->m_lootGSystem->update();
    m_app->m_statsGSystem->update();
}

void GameAppState::render()
{
    m_app->m_rendSubsystem->clear();
    // FIXME: move ViewSystem out of game systems
    m_app->m_viewSystem->render();
    m_app->m_gameGUI->render();
    m_app->m_rendSubsystem->renderPresent();
}

GameAppState* GameAppState::instance()
{
    return &playState;
}
