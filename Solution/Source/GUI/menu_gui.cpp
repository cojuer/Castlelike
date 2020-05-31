#include "menu_gui.h"

#include <SDL.h>

#include "atexture.h"

#include "system__save.h"

#include "widget.h"
#include "widget__button.h"
#include "gui_elem__loading.h"

#include "on_release.h"
#include "options.h"
#include "system__resource.h"
#include "subsystem__render.h"
#include "widget__tabs.h"
#include "text_renderer.h"
#include "font_data.h"
#include "color.h"

#include "subsystem__event.h"
#include "event__menu.h"
#include "listener__menu.h"

namespace gui {

MenuGUI::MenuGUI() :
    m_opts(nullptr),
    m_rendSubsys(nullptr),
    m_resSystem(nullptr),
    m_state(MenuState::ON_MAIN)
{}

MenuGUI::~MenuGUI()
{
    m_reg->removeHandler();
}

bool MenuGUI::init(const Options& opts, 
                   RenderSubsystem& rendSubsys, 
                   ResourceSystem& resSystem,
                   SaveSystem& saveSystem)
{
    setInitialized();

    m_listener.reset(new MenuListener(*this));
    m_reg.reset(EventSubsystem::AddHandler(*m_listener));

    m_opts = &opts;
    m_rendSubsys = &rendSubsys;
    m_resSystem = &resSystem;
    m_saveSystem = &saveSystem;

    initLoadMenu();
    initMMPanel();
    initCredits();

    m_state = MenuState::ON_MAIN;

    return true;
}

bool MenuGUI::initLoadMenu()
{
    assert(isInitialized());

    auto page = m_resSystem->get<Widget>("load_page");

    auto loadMenu = dynamic_cast<LoadingWidget*>(page->getChild("load_menu"));
    loadMenu->init(*m_resSystem, *m_saveSystem);

    m_pages[MenuState::ON_LOAD_MENU] = std::unique_ptr<Widget>(page);

    return true;
}

bool MenuGUI::initMMPanel()
{
    assert(isInitialized());
    auto mainPage = new Widget("mm_panel", nullptr, { 0, 0, 0, 0 }, true, m_resSystem->get<Renderable>("menu_texture"));

    auto mmPanel = dynamic_cast<Widget*>(m_resSystem->get<Widget>("main_menu"));

    auto button = mmPanel->getChild("continue");
    auto event = new MenuEvent(MenuState::ON_CONTINUE);
    button->setBhvr({ new OnRelease(event) });

    button = mmPanel->getChild("but_ng");
    event = new MenuEvent(MenuState::ON_NEW_GAME);
    button->setBhvr({ new OnRelease(event) });

    button = mmPanel->getChild("but_lg");
    event = new MenuEvent(MenuState::ON_LOAD_MENU);
    button->setBhvr({ new OnRelease(event) });

    button = mmPanel->getChild("but_crd");
    event = new MenuEvent(MenuState::ON_CREDITS);
    button->setBhvr({ new OnRelease(event) });

    button = mmPanel->getChild("but_qt");
    event = new MenuEvent(MenuState::ON_QUIT);
    button->setBhvr({ new OnRelease(event) });

    mainPage->addChild(*mmPanel);
    m_pages[MenuState::ON_MAIN] = std::unique_ptr<Widget>(mainPage);

    return true;
}

bool MenuGUI::initCredits()
{
    // TODO: load from data
    assert(isInitialized());
    auto credPage = new Widget("creds_page", m_pages[MenuState::ON_MAIN].get(), { 0, 0, 0, 0 }, true);;

    auto mainPanel = new Widget("creds_panel", nullptr, { 0, 0, std::stoi(m_opts->at(OptType::WIDTH)), std::stoi(m_opts->at(OptType::HEIGHT)) }, true, m_resSystem->get<Renderable>("page_credits"));
    credPage->addChild("credits", *mainPanel);
    m_pages[MenuState::ON_CREDITS] = std::unique_ptr<Widget>(credPage);

    return true;
}

void MenuGUI::handle(SDL_Event& event)
{
    assert(isInitialized());
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
    {
        if (m_state == MenuState::ON_MAIN)
        {
            MenuEvent ev(MenuState::ON_QUIT);
            EventSubsystem::FireEvent(ev);
        }
        else
        {
            m_state = MenuState::ON_MAIN;
        }
        return;
    }
    // FIXME: rework menu states
    if (m_state != MenuState::ON_LOAD &&
        m_state != MenuState::ON_NEW_GAME &&
        m_state != MenuState::ON_QUIT)
    {
        m_pages.at(m_state)->handle(event);
    }
}

void MenuGUI::setState(MenuState state)
{
    assert(isInitialized());
    m_state = state;
}

MenuState MenuGUI::getState() const
{
    assert(isInitialized());
    return m_state;
}

void MenuGUI::render()
{
    assert(isInitialized());
    m_pages.at(m_state)->render(*m_rendSubsys, *m_resSystem);
    renderCursor();
}

void MenuGUI::renderCursor() const
{   
    assert(isInitialized());
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Rect dst = { x, y, 24, 24 };
    m_rendSubsys->render(m_resSystem->get<Renderable>("cursor_simple"), dst);
}

} /* gui namespace. */