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
    App*             m_app;

    static GameAppState playState;
};
