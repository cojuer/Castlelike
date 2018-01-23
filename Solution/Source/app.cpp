#include "app.h"

#include "app_state.h"
#include "system__resource.h"
#include "system__scene.h"
#include "system__save.h"
#include "game_system_manager.h"

#include "system__sound.h"

#include "subsystem__input.h"
#include "subsystem__render.h"
#include "subsystem__rng.h"

#include "game_gui.h"
#include "menu_gui.h"

#include "global_time.h"

App::App() :
    m_running(true),
    m_stateChanged(false), 
    m_rendSubsystem(new RenderSubsystem()),
    m_inputSubsystem(new InputSubsystem()),
    m_rngHolder(new RNGHolder()),
    m_resSystem(new ResourceSystem()),
    m_saveSystem(new SaveSystem()),
    m_sceneSystem(new SceneSystem()),
    m_gameSysManager(new GameSystemManager()),
    m_gameGUI(nullptr),
    m_menuGUI(nullptr),
    m_sEngine(new SoundEngine())
{}

App::~App() = default;

bool App::init()
{
    GlobalTime::instance().start();
    m_opts.loadFile("Castlelike.ini");
    
    // TEST
    m_saveSystem->init();

    bool inited = true;
    inited = inited && m_rendSubsystem->init(m_opts);
    inited = inited && m_resSystem->init(*m_rendSubsystem, *m_rngHolder, m_opts);
    return inited;
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
    if (!m_states.back()->isInited())
    {
        m_states.back()->init(*this);
    }
    m_states.back()->start();
}

void App::pushState(AppState& state)
{
    m_stateChanged = true;
    if (!m_states.empty())
    {
        m_states.back()->pause();
    }
    m_states.push_back(&state);
    if (!m_states.back()->isInited())
    {
        m_states.back()->init(*this);
    }
    m_states.back()->start();
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
