#pragma once

#include "event.h"

enum class DlEvType
{
    NEXT_PHRASE,
    CHOOSE_ANSWER
};

class DlEvent : public Event
{
public:
    DlEvType         type;
    int              answer;

    DlEvent(DlEvType type, int answer = 0, Object* sender = nullptr) :
        Event(sender),
        type(type),
        answer(answer)
    {}
};
