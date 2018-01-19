#include "event__shedule.h"

SheduleEvent::SheduleEvent(std::variant<ActionInterface*, Cutscene*> event, Object* sender) :
    Event(sender),
    m_event(event)
{}

SheduleEvent::~SheduleEvent() 
{};