#include "slot__action.h"

#include "system__resource.h"
#include "subsystem__render.h"

namespace gui {

ActSlot::ActSlot(const std::string& name, Widget* parent, SDL_Rect geometry, const std::string& action) :
    Slot(name, parent, geometry, SlotType::SKILL),
    m_action(action),
    m_img(nullptr)
{}

std::string ActSlot::getAction() const
{
    return m_action;
}

void ActSlot::setAction(std::string actName, ResourceSystem& resSystem)
{
    m_action = actName;
    m_img = resSystem.get<Renderable>(actName);
}

bool ActSlot::isEmpty() const
{
    return m_action.size() == 0;
}

bool ActSlot::handle(SDL_Event& event, Vec2i coordStart)
{
    if (!m_visible) return false;

    int x, y;
    SDL_GetMouseState(&x, &y);
    if (this->isPointOn({x, y}, coordStart) &&
        event.type == SDL_MOUSEBUTTONUP &&
        event.button.button == SDL_BUTTON_LEFT)
    {
        return true;
    }
    return false;
}

void ActSlot::render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem, Vec2i coordStart) const
{
    if (!m_visible) return;

    if (!isEmpty())
    {
        auto renderRect = m_geometry;
        renderRect.x += coordStart.x;
        renderRect.y += coordStart.y;
        rendSubsys.render(m_img, renderRect);
    }
}

} /* gui namespace. */