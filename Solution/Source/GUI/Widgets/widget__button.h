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

    bool             handle(SDL_Event& event, Vec2i coordStart = { 0, 0 }) override;
    void             render(RenderSubsystem& rendSubsystem, ResourceManager& resManager, Vec2i coordStart) const override;

protected:
    void loadGraphics(Json& node, ResourceManager& resManager) override;

private:
    Event*           m_event;
};

}