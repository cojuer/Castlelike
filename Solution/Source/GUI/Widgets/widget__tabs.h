#pragma once

#include <vector>

#include "widget.h"

class Renderable;

namespace gui {

class Button;
class Widget;

using Tab = std::pair<Button*, Widget*>;
using TabVec = std::vector<Tab>;

class TabWidget : public Widget
{
public:
    TabWidget(const std::string& name, Widget* parent, int x, int y, int width, int height, bool visible, Renderable* rendered);

    void             addTab(Button& button, Widget& panel);

    bool             handle(SDL_Event& event, Vec2i coordStart) override;
    void             render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem, Vec2i coordStart) const override;

private:
    TabVec           m_tabs;
    int              m_activeTabNum;
};

}