#pragma once

#include <memory>
#include <vector>

#include "object.h"
#include "options.h"
#include "timer.h"

class ViewSystem;
class SheduleSystem;
class StatsGSystem;
class LootGSystem;
class ControlGSystem;
class AppState;
class JournalSystem;
class ResourceSystem;
class SceneSystem;
class ActorRegistrar;
class SaveSystem;

class SoundEngine;

class InputSubsystem;
class RenderSubsystem;
class RNGHolder;

namespace gui
{
class MenuGUI;
class GameGUI;
}

class App : public Object
{
public:
    App();

    App(const App& another) = delete;
    App(App&& another) = delete;
    App& operator=(const App& other) = delete;
    App& operator=(App&& other) = delete;

    bool             init();
    void             run();
    void             quit();

    void             changeState(AppState& state);
    void             pushState(AppState& state);
    void             popState();

    ~App();

private:
    bool             m_running;
    bool             m_stateChanged;

    Options          m_opts;

    Timer            m_timer;

    std::vector<AppState*> m_states;

    std::unique_ptr<RenderSubsystem> m_rendSubsystem;
    std::unique_ptr<InputSubsystem>  m_inputSubsystem;
    std::unique_ptr<RNGHolder>       m_rngHolder;

    std::unique_ptr<JournalSystem>  m_journalSystem;
    std::unique_ptr<ResourceSystem> m_resSystem;
    std::unique_ptr<SceneSystem>    m_sceneSystem;
    std::unique_ptr<SheduleSystem>  m_sheduleSystem;
    std::unique_ptr<SaveSystem>     m_saveSystem;
    std::unique_ptr<ActorRegistrar> m_actorRegistrar;
    std::unique_ptr<ViewSystem>     m_viewSystem;

    std::unique_ptr<ControlGSystem> m_controlSystem;
    std::unique_ptr<LootGSystem>    m_lootSystem;
    std::unique_ptr<StatsGSystem>   m_statsSystem;
    
    std::unique_ptr<gui::GameGUI>    m_gameGUI;
    std::unique_ptr<gui::MenuGUI>    m_menuGUI;

    bool m_loadSave;
    bool m_loadLast;

    friend class GameAppState;
    friend class MenuAppState;
    friend class LoadingAppState;
};