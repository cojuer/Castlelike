#include "actpanel.h"

#include "resource_manager.h"
#include "subsystem_render.h"

namespace gui {

ActPanel::ActPanel(Widget* parent) :
    Widget(nullptr)
{}

void ActPanel::init(Json& node, ResourceManager& resManager)
{
    loadGeometry(node);
    loadGraphics(node, resManager);
    loadOptions(node);
    if (!m_opts.count("size")) m_opts["size"] = size;
    m_slots.reserve(m_opts.at("size"));
    for (int i = 0; i < m_opts.at("size"); ++i)
    {
        int slotX = lMargin + i * (slWidth + margin);
        m_slots.emplace_back(std::to_string(i), this, SDL_Rect{ slotX, tMargin, slWidth, slHeight }, "");
    }
}

bool ActPanel::handle(SDL_Event& event, Vec2i coordStart)
{
    if (!m_visible) return false;

    coordStart += getPos();
    for (auto& slot: m_slots)
    {
        slot.handle(event, coordStart);
    }
    return true;
}

void ActPanel::render(RenderSubsystem& rendSubsystem, ResourceManager& resManager, Vec2i coordStart) const
{
    if (!m_visible) return;

    auto renderRect = m_geometry;
    renderRect.x += coordStart.x;
    renderRect.y += coordStart.y;
    rendSubsystem.render(m_rendered, renderRect);

    coordStart += getPos();
    for (auto& slot: m_slots)
    {
        slot.render(rendSubsystem, resManager, coordStart);
    }
}

ActPanel::SlotVec& ActPanel::getSlots()
{
    return m_slots;
}

} /* gui namespace. */