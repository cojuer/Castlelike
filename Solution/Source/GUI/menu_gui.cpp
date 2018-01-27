#include "menu_gui.h"

#include <SDL.h>

#include "animation.h"
#include "atexture.h"

#include "system__save.h"

#include "widget.h"
#include "widget__button.h"
#include "gui_elem__loading.h"

#include "on_release.h"
#include "options.h"
#include "factory__renderable.h"
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
    initOptions();
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
    auto mainPage = new Widget("mm_panel", nullptr, { 0, 0, 0, 0 }, true);

    auto mmPanel = dynamic_cast<Widget*>(m_resSystem->get<Widget>("main_menu"));

    auto button = mmPanel->getChild("continue");
    auto event = new MenuEvent(MenuState::ON_NEW_GAME);
    button->setBhvr({ new OnRelease(event) });

    button = mmPanel->getChild("but_ng");
    event = new MenuEvent(MenuState::ON_NEW_GAME);
    button->setBhvr({ new OnRelease(event) });

    button = mmPanel->getChild("but_lg");
    event = new MenuEvent(MenuState::ON_LOAD_MENU);
    button->setBhvr({ new OnRelease(event) });

    button = mmPanel->getChild("but_opt");
    event = new MenuEvent(MenuState::ON_OPTIONS);
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

bool MenuGUI::initOptions()
{
    assert(isInitialized());
    auto optsPage = new Widget("opts_page", m_pages[MenuState::ON_MAIN].get(), { 0, 0, 0, 0 }, true);

    std::string fName = Font::latoRegular;
    int fSize = FontSize::medium;
    auto fColor = Color::white;

    auto optionsWidget = new TabWidget("opts_tabs", nullptr, 0, 0, 820, 460, true, nullptr);

    auto testButton = new Button("opts", optionsWidget, { 80, 40, 0, 0 }, true, m_resSystem->get<Renderable>("text_common"));
    auto testPanel = new Widget("opts_panel", optionsWidget, { 250, 40, 600, 600 }, true, m_resSystem->get<Renderable>("main_background"));

    testPanel->addChild(*new Widget("1", testPanel, 20, 20, true, m_resSystem->textRenderer->renderTexture("Resolution", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("2", testPanel, 20, 40, true, m_resSystem->textRenderer->renderTexture("Music", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("3", testPanel, 20, 60, true, m_resSystem->textRenderer->renderTexture("Effects", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("4", testPanel, 20, 80, true, m_resSystem->textRenderer->renderTexture("Difficulty", fName, fSize, fColor)));

    optionsWidget->addTab(testButton, testPanel);

    testButton = new Button("controls", optionsWidget, { 80, 70, 0, 0 }, true, m_resSystem->get<Renderable>("text_controls"));
    testPanel = new Widget("controls_panel", optionsWidget, { 250, 40, 600, 600 }, true, m_resSystem->get<Renderable>("main_background"));
    optionsWidget->addTab(testButton, testPanel);

    testPanel->addChild(*new Widget("5", testPanel, 20, 20, true, m_resSystem->textRenderer->renderTexture("move up", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("6", testPanel, 20, 40, true, m_resSystem->textRenderer->renderTexture("move down", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("7", testPanel, 20, 60, true, m_resSystem->textRenderer->renderTexture("move left", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("8", testPanel, 20, 80, true, m_resSystem->textRenderer->renderTexture("move right", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("9", testPanel, 20, 100, true, m_resSystem->textRenderer->renderTexture("show hero info", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("10", testPanel, 20, 120, true, m_resSystem->textRenderer->renderTexture("show bag", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("11", testPanel, 20, 140, true, m_resSystem->textRenderer->renderTexture("show equipment", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("12", testPanel, 300, 20, true, m_resSystem->textRenderer->renderTexture("quick slot 1", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("13", testPanel, 300, 40, true, m_resSystem->textRenderer->renderTexture("quick slot 2", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("14", testPanel, 300, 60, true, m_resSystem->textRenderer->renderTexture("quick slot 3", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("15", testPanel, 300, 80, true, m_resSystem->textRenderer->renderTexture("quick slot 4", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("16", testPanel, 300, 100, true, m_resSystem->textRenderer->renderTexture("quick slot 5", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("17", testPanel, 300, 120, true, m_resSystem->textRenderer->renderTexture("quick slot 6", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("18", testPanel, 300, 140, true, m_resSystem->textRenderer->renderTexture("quick slot 7", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("19", testPanel, 300, 160, true, m_resSystem->textRenderer->renderTexture("quick slot 8", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("20", testPanel, 300, 180, true, m_resSystem->textRenderer->renderTexture("quick slot 9", fName, fSize, fColor)));
    testPanel->addChild(*new Widget("21", testPanel, 300, 200, true, m_resSystem->textRenderer->renderTexture("quick slot 10", fName, fSize, fColor)));

    optsPage->addChild("main_tab", *optionsWidget);
    m_pages[MenuState::ON_OPTIONS] = std::unique_ptr<Widget>(optsPage);
    return true;
}

bool MenuGUI::initCredits()
{
    // TODO: load from data
    assert(isInitialized());
    auto credPage = new Widget("creds_page", m_pages[MenuState::ON_MAIN].get(), { 0, 0, 0, 0 }, true);;

    auto mainPanel = new Widget("creds_panel", nullptr, { 0, 0, std::stoi(m_opts->at(OptType::WIDTH)), std::stoi(m_opts->at(OptType::HEIGHT)) }, true);
    auto title = m_resSystem->textRenderer->renderTexture("Credits aren't available in this version", Font::latoRegular, 40, { 255, 165, 0 });
    SDL_Rect dst = { (m_opts->getInt(OptType::WIDTH) - title->getWidth()) / 2,
                     (m_opts->getInt(OptType::HEIGHT) - title->getHeight()) / 2,
                     title->getWidth(),
                     title->getHeight() };
    auto textPanel = new Widget("text", mainPanel, dst, true, title);
    mainPanel->addChild("pan_txt", *textPanel);

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
    m_pages.at(m_state)->handle(event);
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