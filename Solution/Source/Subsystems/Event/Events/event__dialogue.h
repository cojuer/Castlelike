#pragma once

#include "event.h"

enum class DlEvType
{
    START_DL,
    NEXT_PHRASE,
    CHOOSE_ANSWER
};

/* 
    FIXME: different dl events should have absolutely different structure,
    now it is mess of attributes of all of them 
*/
class DlEvent : public Event
{
public:
    DlEvType         type;
    int              answer;
    int              dl_id;

    DlEvent(DlEvType type, int answer = 0, Object* sender = nullptr, int dl_id = -1) :
        Event(sender),
        type(type),
        answer(answer),
        dl_id(dl_id)
    {}
};
