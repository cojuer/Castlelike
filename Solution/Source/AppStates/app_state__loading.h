#pragma once

#include "app_state.h"

class LoadingAppState final : public AppState
{
public:
    LoadingAppState();

    void             init(App& app) override;
    void             clean() override;

    void             start() override;
    void             pause() override;
    void             resume() override;

    void             handle() override;
    void             update() override;
    void             render() override;

    static LoadingAppState* instance();

private:
    App*               m_app;

    static LoadingAppState playState;
};
