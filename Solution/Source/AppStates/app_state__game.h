#pragma once

#include "app_state.h"

class GameAppState final : public AppState
{
public:
    GameAppState() = default;

    void             init(App& app) override;
    void             clean() override;

    void             start() override;
    void             pause() override;
    void             resume() override;

    void             handle() override;
    void             update() override;
    void             render() override;

    static GameAppState* instance();

private:
    App*             m_app { nullptr };

    static GameAppState playState;
};
