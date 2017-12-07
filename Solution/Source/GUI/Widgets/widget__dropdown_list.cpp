#include "widget__dropdown_list.h"

#include <iostream> // TEST

#include "spritesheet.h"

namespace gui {

DropDownList::DropDownList(const std::string& name, Widget* parent, SDL_Rect geometry, bool visible) :
    Widget(name, parent, geometry, visible),
    m_button(new Button("main", this, { 0, 0, 0, 0 }, true, nullptr, nullptr)),
    m_opened(false)
{}

void DropDownList::addChild(Widget& widget)
{
    auto offset = widget.getHeight();
    for (auto& pair : m_children)
    {
        offset += pair.second->getHeight();
    }
    widget.setPosition({ m_geometry.x, offset });
    m_children[widget.getName()] = std::unique_ptr<Widget>(&widget);
    if (m_children.size() == 1)
    {
        auto activeChild = m_children.cbegin();
        m_active = activeChild->first;
        auto activeGraphicsCopy = activeChild->second->getGraphics()->clone();
        m_button->freeGraphics();
        m_button->setGraphics(activeGraphicsCopy);
    }
}

bool DropDownList::handle(SDL_Event& event, Vec2i coordStart)
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
        for (auto& pair : m_children)
        {
            oldState = pair.second->getState();
            handle = pair.second->handle(event, coordStart);
            newState = pair.second->getState();
            if (handle &&
                oldState == WState::PRESSED &&
                newState == WState::MOUSE_OVER)
            {
                m_active = pair.first;
                auto activeGraphicsCopy = pair.second->getGraphics()->clone();
                m_button->freeGraphics();
                m_button->setGraphics(activeGraphicsCopy);
                m_opened = false;
                break;
            }
        }
    }
    return true;
}

void DropDownList::render(RenderSubsystem& rendSubsys, ResourceManager& resManager, Vec2i coordStart) const
{
    if (!m_visible) return;
    coordStart += getPos();
    m_button->render(rendSubsys, resManager, coordStart);
    if (m_opened)
    {
        for (auto& pair : m_children)
        {
            pair.second->render(rendSubsys, resManager, coordStart);
        }
    }
}

} /* gui namespace. */