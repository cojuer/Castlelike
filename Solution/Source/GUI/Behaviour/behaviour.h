#pragma once

#include <SDL.h>

#include <map>
#include <vector>

#include "vec2.h"
#include "widget_state.h"

namespace gui {

class Trigger;
class Widget;

class Bhvr
{
    using KeyTrigMap = std::map<SDL_Keycode, Trigger*>;
    using TrigVec    = std::vector<Trigger*>;

public:
    Bhvr(Widget& parent, TrigVec&& triggers);
    ~Bhvr();

    WState          behave(SDL_Event& ev, Vec2i coordStart = { 0, 0 });

private:
    void changeState(SDL_Event& event, Vec2i coordStart);

private:
    Widget&         m_parent;

    TrigVec         m_trigs;
    KeyTrigMap      m_keyTrigs;
};

} /* gui namespace. */