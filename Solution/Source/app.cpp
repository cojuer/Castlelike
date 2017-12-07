#include "app.h"

#include "app_state.h"
#include "resource_manager.h"
#include "scene_manager.h"
#include "system_manager.h"

#include "system__sound.h"

#include "subsystem_input.h"
#include "subsystem_render.h"

#include "game_gui.h"
#include "menu_gui.h"

#include "global_time.h"

App::App() :
    m_running(true),
    m_stateChanged(false), 
    m_rendSubsystem(new RenderSubsystem()),
    m_inputSubsystem(new InputSubsystem()),
    m_resManager(new ResourceManager()),
    m_sceneManager(new SceneManager()),
    m_sysManager(new SystemManager()),
    m_gameGUI(nullptr),
    m_menuGUI(nullptr),
    m_sEngine(new SoundEngine())
{}

App::~App() = default;

bool App::init() 
{
    GlobalTime::instance().start();
    m_opts.loadFile("Castlelike.ini");
    return m_rendSubsystem->init(m_opts) &&
           m_resManager->init(*m_rendSubsystem, m_opts);
    // Sound system is not properly implemented
    // m_sEngine->init();
}

void App::run()
{
    while (m_running && !m_states.empty())
    {
        m_states.back()->handle();
        if (!m_running) break;
        if (m_stateChanged) { m_stateChanged = false; continue; }
        m_states.back()->update();
        if (!m_running) break;
        if (m_stateChanged) { m_stateChanged = false; continue; }
        m_states.back()->render();
    }
}

void App::changeState(AppState& state)
{
    m_stateChanged = true;
    if (!m_states.empty())
    {
        m_states.back()->clean();
        m_states.pop_back();
    }
    m_states.push_back(&state);
    m_states.back()->init(*this);
}

void App::pushState(AppState& state)
{
    m_stateChanged = true;
    if (!m_states.empty())
    {
        m_states.back()->pause();
    }

    m_states.push_back(&state);
    m_states.back()->init(*this);
}

void App::popState()
{
    m_stateChanged = true;
    if (!m_states.empty())
    {
        m_states.back()->clean();
        m_states.pop_back();
    }
    if (!m_states.empty())
    {
        m_states.back()->resume();
    }
}

void App::quit()
{
    m_running = false;
}
