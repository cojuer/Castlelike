#pragma once

#include <iostream>

#include "event__text.h"
#include "event_handler.h"
#include "journal.h"

class TextListener : public EventHandler<TextEvent>
{
private:
    Journal& tBuffer;
public:
    TextListener(Journal& tBuffer) :
        tBuffer(tBuffer)
    {}

    void onEvent(TextEvent& event) override
    {
        std::cout << "on journal event" << std::endl;
        tBuffer.addEntry(event.type, event.args);
    }
};