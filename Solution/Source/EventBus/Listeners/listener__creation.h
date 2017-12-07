#pragma once

#include "ccreationgui.h"
#include "event__creation.h"
#include "event_handler.h"
#include "text_manager.h"

class CreationListener : public EventHandler<CreationEvent>
{
private:
    gui::CreationUI* ccgui;

public:
    CreationListener(gui::CreationUI* ccgui) :
        ccgui(ccgui)
    {}

    void onEvent(CreationEvent& event) override
    {
        auto& tManager = TextManager::instance();
        auto& points = ccgui->m_attrPoints;
        auto& attributes = ccgui->m_resAttrs;

        //std::cout << "on CC event" << std::endl;
        switch (event.type)
        {
        case CreationEvType::INC:
            if (points > 0)
            {
                --points;
                ++attributes[event.attrType];
            }
            break;
        case CreationEvType::DEC:
            if (attributes[event.attrType] > 0)
            {
                ++points;
                --attributes[event.attrType];
            }
            break;
        case CreationEvType::SET:
            ccgui->m_desc = tManager.getDescription(event.attrType);
        }
    }
};