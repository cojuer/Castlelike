#pragma once

#include <queue>
#include <variant>

#include "system__cutscene.h"
#include "cutscene.h"

#include "event_handler.h"
#include "event__shedule.h"

using ShedulerEvent = std::variant<ActionInterface*, Cutscene*>;

class SheduleSystem final : public EventHandler<SheduleEvent>
{
public:
    SheduleSystem();

    bool init();

    bool isSheduleEmpty() const;
    void refresh();

    void onEvent(SheduleEvent& event) override;

private:
    CutsceneSystem m_player;
    std::queue<ShedulerEvent> m_eventQueue;
};