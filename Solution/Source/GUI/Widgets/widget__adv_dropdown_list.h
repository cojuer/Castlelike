#pragma once

#include "widget__button.h"
#include "widget.h"

namespace gui {

class Button;

class AdvDropDownList : public Widget
{
public:
    AdvDropDownList(const std::string& name, Widget* parent, SDL_Rect geometry, bool visible);

    void addChild(Widget& widget) override;

    bool handle(SDL_Event& event, Vec2i coordStart = { 0, 0 }) override;
    void render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem, Vec2i coordStart = { 0, 0 }) const override;
private:
    Button*     m_button;
    std::string m_active;
    bool        m_opened;
};

}