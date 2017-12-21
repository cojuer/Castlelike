#pragma once

#include <queue>
#include <variant>

#include "cutscene.h"
#include "cutscene_player.h"

#include "component__graphics_interface.h"

#include "event__shedule.h"
#include "event_handler.h"

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