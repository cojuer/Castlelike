#pragma once

#include "widget.h"

class Event;
class SprSheet;

namespace gui {

class Button : public Widget
{
public:
    explicit Button(Widget* parent = nullptr);
    Button(const std::string& name, Widget* parent, SDL_Rect geometry, bool visible, Renderable* sprSheet, Event* event = nullptr);

    void             setGraphics(Renderable* rendered) override;

    bool             handle(SDL_Event& event, Vec2i coordStart) override;
    void             render(RenderSubsystem& rendSubsystem, ResourceSystem& resSystem, Vec2i coordStart) const override;

protected:
    void loadGraphics(Json& node, ResourceSystem& resSystem) override;
};

}