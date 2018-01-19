#pragma once

#include <memory>
#include <vector>

#include "object.h"
#include "options.h"
#include "timer.h"

class AppState;
class ResourceSystem;
class SceneSystem;
class GameSystemManager;
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

    std::unique_ptr<ResourceSystem> m_resSystem;
    std::unique_ptr<SceneSystem>    m_sceneSystem;
    std::unique_ptr<SaveSystem>     m_saveSystem;
    std::unique_ptr<GameSystemManager> m_gameSysManager;
    
    std::unique_ptr<gui::GameGUI>    m_gameGUI;
    std::unique_ptr<gui::MenuGUI>    m_menuGUI;
    
    std::unique_ptr<SoundEngine>     m_sEngine;

    bool m_use_save;
    std::string profile;
    std::string save;

    friend class GameAppState;
    friend class MenuAppState;
    friend class LoadingAppState;
};