#pragma once

#include <iostream>

#include "system__dialogue.h"
#include "event__dialogue.h"
#include "event_handler.h"

class DlListener : public EventHandler<DlEvent>
{
private:
    DialManager& dlManager;
public:
    DlListener(DialManager& dlManager) :
        dlManager(dlManager)
    {}

    void onEvent(DlEvent& event) override
    {
        std::cout << "on dialogue event" << std::endl;
        switch (event.type)
        {
        case DlEvType::START_DL:
            dlManager.startDial(event.dl_id);
            break;
        case DlEvType::NEXT_PHRASE:
            dlManager.nextPhrase();
            break;
        case DlEvType::CHOOSE_ANSWER:
            dlManager.nextState(event.answer);
            break;
        }
    }
};
