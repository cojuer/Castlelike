#include "widget__adv_dropdown_list.h"

#include "spritesheet.h"

namespace gui {

AdvDropDownList::AdvDropDownList(const std::string& name, Widget* parent, SDL_Rect geometry, bool visible) :
    Widget(name, parent, geometry, visible),
    m_button(new Button("main", this, { 0, 0, 0, 0 }, true, nullptr, nullptr)),
    m_opened(false)
{}

void AdvDropDownList::addChild(Widget& widget)
{
    auto offset = widget.getHeight();
    for (auto&[name, child] : m_children)
    {
        offset += child->getHeight();
    }
    widget.setPosition({ m_geometry.x, offset });
    m_children[widget.getName()] = std::unique_ptr<Widget>(&widget);
    if (m_children.size() == 1)
    {
        auto activeChild = m_children.cbegin();
        m_active = activeChild->first;
        // FIXME: what if graphics == nullptr
        auto activeGraphicsCopy = activeChild->second->getGraphics()->clone();
        m_button->freeGraphics();
        m_button->setGraphics(activeGraphicsCopy);
    }
}

bool AdvDropDownList::handle(SDL_Event& event, Vec2i coordStart)
{
    if (!m_visible) return false;
    coordStart += getPos();
    auto oldState = m_button->getState();
    auto handle = m_button->handle(event, coordStart);
    auto newState = m_button->getState();
    if (handle &&
        oldState == WState::PRESSED && 
        newState == WState::MOUSE_OVER)
    {
        m_opened = !m_opened;
    }
    if (m_opened)
    {
        for (auto&[name, child] : m_children)
        {
            oldState = child->getState();
            handle = child->handle(event, coordStart);
            newState = child->getState();
            if (handle &&
                oldState == WState::PRESSED &&
                newState == WState::MOUSE_OVER)
            {
                m_active = name;
                auto activeGraphicsCopy = child->getGraphics()->clone();
                m_button->freeGraphics();
                m_button->setGraphics(activeGraphicsCopy);
                m_opened = false;
                break;
            }
        }
    }
    return true;
}

void AdvDropDownList::render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem, Vec2i coordStart) const
{
    if (!m_visible) return;

    coordStart += getPos();
    m_button->render(rendSubsys, resSystem, coordStart);
    
    if (!m_opened) return;
    
    for (auto&[name, child] : m_children)
    {
        child->render(rendSubsys, resSystem, coordStart);
    }
}

} /* gui namespace. */