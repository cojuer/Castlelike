#pragma once

#include <SDL.h>

#include <map>
#include <memory>
#include <vector>

#include "vec2.h"
#include "widget_state.h"
#include "trigger.h"

namespace gui {

class Widget;

class Bhvr
{
    using KeyTrigMap = std::map<SDL_Keycode, std::unique_ptr<Trigger>>;
    using TrigVec    = std::vector<std::unique_ptr<Trigger>>;

public:
    Bhvr(Widget& parent, std::vector<Trigger*>&& triggers);

    void            behave(SDL_Event& ev, Vec2i coordStart = { 0, 0 });

private:
    void changeState(SDL_Event& event, Vec2i coordStart);

private:
    Widget&         m_parent;

    TrigVec         m_trigs;
    KeyTrigMap      m_keyTrigs;
};

} /* gui namespace. */