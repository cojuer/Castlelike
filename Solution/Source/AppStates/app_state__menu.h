#pragma once

#include "app.h"
#include "app_state.h"

#include "event_handler.h"
#include "event__menu.h"

class MenuAppState final : public AppState, EventHandler<MenuEvent>
{
public:

	MenuAppState::MenuAppState();

    void             init(App& app) override;
    void             clean() override;

    void             start() override;
    void             pause() override;
    void             resume() override;

    void             handle() override;
    void             update() override;
    void             render() override;

    void             onEvent(MenuEvent& event) override;

    static MenuAppState* instance();

private:
	App*             m_app;

	static MenuAppState menuAppState;
};
