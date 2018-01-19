#pragma once

#include <iostream>

#include "ccreationgui.h"
#include "event_handler.h"
#include "text_manager.h"
#include "event__ui_trait.h"

class UI_TraitListener : public EventHandler<UI_TraitEvent>
{
public:
    UI_TraitListener(gui::CreationUI& ui) :
        ui(ui)
    {}

    void onEvent(UI_TraitEvent& event) override
    {
        auto& tManager = TextManager::instance();

        std::cout << "on trait event" << std::endl;
        
        ui.m_trait = event.trait;
        auto query = std::string("trait_") + ui.m_trait;
        ui.m_desc = tManager.getDescription(query);
    }

private:
    gui::CreationUI& ui;
};
