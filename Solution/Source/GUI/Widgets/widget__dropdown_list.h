#pragma once

#include "widget.h"
#include "widget__button.h"

#include "text_info.h"

namespace gui {

class Button;

class DropDownList : public Widget
{
public:
    DropDownList(const std::string& name, 
                 Widget* parent, 
                 SDL_Rect geometry, 
                 bool visible);

    void addElem(std::string elem, ResourceSystem& resSystem);

    void setActiveElem(const std::string& active);
    const std::string& getActiveElem() const;

    bool handle(SDL_Event& event, Vec2i coordStart) override;
    void render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem, Vec2i coordStart) const override;
private:
    Button*     m_button;
    std::string m_active;
    bool        m_opened;
};

}