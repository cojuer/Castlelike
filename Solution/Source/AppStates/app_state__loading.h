#pragma once

#include "app_state.h"

#include "event_handler.h"
#include "event__load.h"

class HandlerRegistration;

class LoadingAppState final : public AppState, EventHandler<LoadEvent>
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

    void onEvent(LoadEvent& event) override;

private:
    App*               m_app;

    std::string m_profile;
    std::string m_save;

    std::unique_ptr<HandlerRegistration> reg;

    static LoadingAppState playState;
};
