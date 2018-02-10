#pragma once

#include "event.h"

#include <variant>

#include "action_interface.h"
#include "cutscene.h"

class SheduleEvent final : public Event
{
public:
    std::variant<ActionInterface*, Cutscene*> m_event;

    explicit SheduleEvent(std::variant<ActionInterface*, Cutscene*> event, Object* sender = nullptr);
};
