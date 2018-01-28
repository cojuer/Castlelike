#include "widget__dropdown_list.h"

#include "system__resource.h"
#include "text_renderer.h"

#include "spritesheet.h"
#include "color.h"

namespace gui {

DropDownList::DropDownList(const std::string& name, Widget* parent, SDL_Rect geometry, bool visible) :
    Widget(name, parent, geometry, visible),
    m_button(new Button("main", this, { 0, 0, geometry.w, geometry.h }, true, nullptr, nullptr)),
    m_opened(false)
{}

void DropDownList::addElem(std::string elem, ResourceSystem& resSystem)
{
    // FIXME: magic consts
    auto button = new Button{ elem, this, {0,0,m_geometry.w,m_geometry.h}, true, nullptr, nullptr };
    button->setGUIText({ { Font::latoBold, uint32_t(FontSize::medium), Color::silver, 100 }, elem });

    auto offset = m_button->getHeight();
    for (auto&[name, child] : m_children)
    {
        offset += child->getHeight();
    }
    button->setPosition({ 0, offset });
    addChild(*button);
    
    if (m_children.size() == 1)
    {
        m_active = m_children.cbegin()->first;
        m_button->setGUIText(m_children.at(m_active)->getGUIText());
    }
}

void DropDownList::setActiveElem(const std::string& active)
{
    assert(m_children.find(active) != m_children.end());
    m_active = active;
    m_button->setGUIText(m_children.at(m_active)->getGUIText());
    m_opened = false;
}

const std::string& DropDownList::getActiveElem() const
{
    return m_active;
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
    if (!m_opened) return true;

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
            m_button->setGUIText(m_children.at(m_active)->getGUIText());
            m_opened = false;
            break;
        }
    }
    return true;
}

void DropDownList::render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem, Vec2i coordStart) const
{
    if (!m_visible) return;

    coordStart += getPos();
    m_button->render(rendSubsys, resSystem, coordStart);

    renderText(rendSubsys, resSystem, coordStart);

    if (!m_opened) return;

    for (auto&[name, child] : m_children)
    {
        child->render(rendSubsys, resSystem, coordStart);
    }
}

} /* gui namespace. */