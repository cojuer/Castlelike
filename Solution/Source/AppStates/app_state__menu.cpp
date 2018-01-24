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

    m_app->m_menuGUI.reset(new gui::MenuGUI());
    m_app->m_menuGUI->init(m_app->m_opts, *m_app->m_rendSubsystem, *m_app->m_resSystem);
}

void MenuAppState::clean() {}

void MenuAppState::start() {}

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
    
}

void MenuAppState::render()
{
    m_app->m_rendSubsystem->clear();
    m_app->m_menuGUI->render();
    m_app->m_rendSubsystem->renderPresent();
}

void MenuAppState::onEvent(MenuEvent& event)
{
    switch (event.newState)
    {
    case MenuState::ON_NEW_GAME:
        m_app->m_loadSave = false;
        m_app->changeState(*LoadingAppState::instance());
        break;
    case MenuState::ON_LOAD:
        m_app->m_loadSave = true;
        // TODO: use special menu to choose save
        m_app->m_saveSystem->useProfile("test");
        m_app->changeState(*LoadingAppState::instance());
        break;
    case MenuState::ON_QUIT:
        m_app->quit();
        break;
	default:
		break;
    }
}

MenuAppState* MenuAppState::instance()
{
    return &menuAppState;
}
