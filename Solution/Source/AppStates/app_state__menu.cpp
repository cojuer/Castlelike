#include "app_state__menu.h"

#include "subsystem_render.h"

#include "app_state__loading.h"

#include "subsystem__event.h"
#include "listener__menu.h"

#include "menu_gui.h"

MenuAppState MenuAppState::menuAppState;

MenuAppState::MenuAppState() :
    m_app(nullptr)
{}

void MenuAppState::init(App& app)
{
    EventSubsystem::AddHandler<MenuEvent>(*this);

    m_app = &app;

    m_app->m_menuGUI.reset(new gui::MenuGUI());
    m_app->m_menuGUI->init(m_app->m_opts, *m_app->m_rendSubsystem, *m_app->m_resSystem);
}

void MenuAppState::clean() {}

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
    case MenuState::ON_LOAD:
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
