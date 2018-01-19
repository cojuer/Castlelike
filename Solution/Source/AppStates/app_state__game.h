#pragma once

#include "app_state.h"
#include "vec2.h"

class GameAppState final : public AppState
{
public:
    GameAppState();

    void             init(App& app) override;
    void             clean() override;

    void             pause() override;
    void             resume() override;

    void             handle() override;
    void             update() override;
    void             render() override;

    static GameAppState* instance();

private:
    void             save();

private:
    App*             m_app;
    Options*         m_opts;

    SceneSystem*    m_sceneSystem;
    GameSystemManager*   m_sysManager;

    static GameAppState playState;
};
