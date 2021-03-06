#pragma once

#include "widget.h"

class SaveSystem;

namespace gui {

class Button;
class DropDownList;

class LoadingWidget : public Widget
{
public:
    LoadingWidget(Widget* parent = nullptr);
    LoadingWidget(const std::string& name,
                  Widget* parent,
                  SDL_Rect rect,
                  bool visible,
                  Renderable* rendered = nullptr);

    void init(ResourceSystem& resSystem, SaveSystem& saveSystem);

    bool handle(SDL_Event& event, Vec2i coordStart) override; 
    void refresh();

private:
    ResourceSystem* m_resSystem;
    SaveSystem* m_saveSystem;

    DropDownList* m_profMenu;
    std::map<std::string, Button*> m_saveButtons;
};

} /* gui namespace. */