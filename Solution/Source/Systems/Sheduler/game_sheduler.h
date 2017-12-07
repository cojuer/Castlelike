#pragma once

#include <queue>
#include <variant>

#include "cutscene.h"
#include "component__graphics_interface.h"
#include "component__stateful_graphics.h"
#include "event__shedule.h"
#include "event_handler.h"
#include "cutscene_player.h"

using ShedulerEvent = std::variant<ActionInterface*, Cutscene*>;

class Sheduler final : public EventHandler<SheduleEvent>
{
public:
    Sheduler();

    bool init();

    bool isSheduleEmpty() const;
    void refresh();

    void onEvent(SheduleEvent& event) override;

private:
    CutscenePlayer m_player;
    std::queue<ShedulerEvent> m_eventQueue;
};