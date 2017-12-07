#pragma once

#include "bagwidget.h"
#include "equipmentwidget.h"
#include "game_gui.h"
#include "actpanel.h"

#include "event_handler.h"
#include "event__gui.h"

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
            iggui.m_dialWdg->setVisible(true);
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
