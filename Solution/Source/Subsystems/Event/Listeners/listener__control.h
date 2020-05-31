#pragma once

#include <iostream>

#include "player_controller.h"
#include "event__control.h"
#include "event_handler.h"

class ControlListener : public EventHandler<ControlEvent>
{
private:
    PlayerController& controller;
public:
    ControlListener(PlayerController& controller) :
        controller(controller)
    {}

    void onEvent(ControlEvent& event) override
    {
        std::cout << "on control event" << std::endl;
        switch (event.m_state)
        {
        case CONTROL::ENABLE:
            controller.set_to_control(true);
            break;
        case CONTROL::DISABLE:
            controller.set_to_control(false);
            break;
        default:
            break;
        }
    }
};
