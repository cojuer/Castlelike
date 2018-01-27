#include "app_state__menu.h"

#include "app_state__loading.h"

#include "subsystem__event.h"
#include "subsystem__render.h"
#include "system__save.h"

#include "listener__menu.h"
#include "menu_gui.h"

MenuAppState MenuAppState::menuAppState;

MenuAppState::MenuAppState() :
    m_app(nullptr)
{}

void MenuAppState::init(App& app)
{
    m_initialized = true;
    EventSubsystem::AddHandler<MenuEvent>(*this);

    m_app = &app;
}

void MenuAppState::clean()
{
    m_app->m_menuGUI.reset(nullptr);
}

void MenuAppState::start()
{
    m_app->m_menuGUI.reset(new gui::MenuGUI());
    m_app->m_menuGUI->init(m_app->m_opts,
                           *m_app->m_rendSubsystem,
                           *m_app->m_resSystem,
                           *m_app->m_saveSystem);
}

void MenuAppState::pause() {}

void MenuAppState::resume() {}

void MenuAppState::handle()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_app->quit();
            break;
		default:
			break;
        }
        m_app->m_menuGUI->handle(event);
    }
}

void MenuAppState::update()
{
    switch (m_app->m_menuGUI->getState())
    {
    case MenuState::ON_CONTINUE:
        m_app->m_loadSave = true;
        m_app->m_loadLast = true;
        m_app->changeState(*LoadingAppState::instance());
        break;
    case MenuState::ON_NEW_GAME:
        m_app->m_loadSave = false;
        m_app->changeState(*LoadingAppState::instance());
        break;
    case MenuState::ON_LOAD:
        m_app->m_loadSave = true;
        m_app->m_loadLast = false;
        m_app->changeState(*LoadingAppState::instance());
        break;
    case MenuState::ON_QUIT:
        m_app->quit();
        break;
    default:
        break;
    }
}

void MenuAppState::render()
{
    m_app->m_rendSubsystem->clear();
    m_app->m_menuGUI->render();
    m_app->m_rendSubsystem->renderPresent();
}

void MenuAppState::onEvent(MenuEvent& event)
{
    m_app->m_menuGUI->setState(event.newState);
}

MenuAppState* MenuAppState::instance()
{
    return &menuAppState;
}
