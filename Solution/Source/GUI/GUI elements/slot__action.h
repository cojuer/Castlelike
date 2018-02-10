#pragma once

#include "atexture.h"
#include "widget__slot.h"
#include "action_manager.h"

class ResourceSystem;

namespace gui {

class ActSlot : public Slot
{
public:
    ActSlot(const std::string& name, Widget* parent, SDL_Rect geometry, std::string action);

    std::string getAction() const;
    void setAction(std::string actName, ResourceSystem& resSystem);
   
    bool isEmpty() const override;

    bool handle(SDL_Event& event, Vec2i coordStart) override;
    void render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem, Vec2i coordStart) const override;

private:
    std::string  m_action;
    ActionArgs     m_input;
    // FIXME: use standart m_rendered
    Renderable*  m_img;
};

} /* gui namespace. */