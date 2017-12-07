#pragma once

#include "atexture.h"
#include "widget__slot.h"
#include "action_manager.h"

class ResourceManager;

namespace gui {

class ActSlot : public Slot
{
public:
    ActSlot(const std::string& name, Widget* parent, SDL_Rect geometry, const std::string& action);

    std::string getAction() const;
    void setAction(std::string actName, ResourceManager& resManager);
   
    bool isEmpty() const override;

    bool handle(SDL_Event& event, Vec2i coordStart = { 0, 0 }) override;
    void render(RenderSubsystem& rendSubsys, ResourceManager& resManager, Vec2i coordStart = { 0, 0 }) const override;

private:
    std::string  m_action;
    ActionArgs     m_input;
    // FIXME: use standart m_rendered
    Renderable*  m_img;
};

} /* gui namespace. */