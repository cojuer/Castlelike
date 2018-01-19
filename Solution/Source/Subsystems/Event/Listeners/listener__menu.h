#pragma once

#include "event__menu.h"
#include "event_handler.h"
#include "menu_gui.h"

class MenuListener : public EventHandler<MenuEvent>
{
public:
    MenuListener(gui::MenuGUI& menuGUI) :
        m_menuGUI(menuGUI)
    {}

    void onEvent(MenuEvent& event) override
    {
        m_menuGUI.setState(event.newState);
    }

private:
    gui::MenuGUI& m_menuGUI;
};
