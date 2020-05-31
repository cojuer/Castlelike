#pragma once

#include "gui_elem__bag_widget.h"
#include "game_gui.h"

#include "event_handler.h"
#include "event__gui.h"
#include "event__control.h"

class GUIListener : public EventHandler<GUIEvent>
{
private:
    gui::GameGUI& iggui;
public:
    GUIListener(gui::GameGUI& iggui) :
        iggui(iggui)
    {}

    void onEvent(GUIEvent& event) override
    {
        std::cout << "on gui event" << std::endl;
        switch (event.id)
        {
        case EventId::HERO_MOVED:
            iggui.resetActiveSlot();
            iggui.m_bagWdg->resetSlots();
            iggui.m_lootWdg->resetSlots();
            iggui.m_lootWdg->setVisible(false);
            break;
        case EventId::START_DIALOG:
            EventSubsystem::FireEvent(*new ControlEvent(CONTROL::DISABLE));
            iggui.m_dialWdg->setVisible(true);
            iggui.setState(gui::GameGUIState::DIALOGUE);
            iggui.refreshDlMenu();
            break;
        case EventId::REFRESH_DIALOG:
            iggui.refreshDlMenu();
            break;
        default:
            break;
        }
    }
};
