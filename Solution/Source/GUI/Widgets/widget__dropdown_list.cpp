#include "widget__dropdown_list.h"

#include "system__resource.h"
#include "text_renderer.h"

#include "spritesheet.h"
#include "color.h"

namespace gui {

DropDownList::DropDownList(const std::string& name, Widget* parent, SDL_Rect geometry, bool visible) :
    Widget(name, parent, geometry, visible),
    m_button(new Button("main", this, { 0, 0, 0, 0 }, true, nullptr, nullptr)),
    m_opened(false)
{}

void DropDownList::addElem(std::string elem, ResourceSystem& resSystem)
{
    // FIXME: memory leak
    auto sprites = new SprSheet{
        std::vector<ATexture*>{
            resSystem.textRenderer->renderTexture(elem, Font::latoBold, FontSize::medium, Color::silver),
            resSystem.textRenderer->renderTexture(elem, Font::latoBold, FontSize::medium, Color::silver),
            resSystem.textRenderer->renderTexture(elem, Font::latoBold, FontSize::medium, Color::silver),
            resSystem.textRenderer->renderTexture(elem, Font::latoBold, FontSize::medium, Color::silver),
            resSystem.textRenderer->renderTexture(elem, Font::latoBold, FontSize::medium, Color::silver)
        }
    };

    auto button = new Button{ elem, this, {0,0,20,100}, true, sprites, nullptr };
    addChild(*button);

    auto offset = button->getHeight();
    for (auto&[name, child] : m_children)
    {
        offset += child->getHeight();
    }
    button->setPosition({ 0, offset });
    
    if (m_children.size() == 1)
    {
        m_active = m_children.cbegin()->first;
        m_button->freeGraphics();
        m_button->setGraphics(sprites->clone());
    }
}

void DropDownList::setActiveElem(const std::string& active)
{
    assert(m_children.find(active) != m_children.end());
    m_active = active;
    auto activeGraphicsCopy = m_children.at(m_active)->getGraphics()->clone();
    m_button->freeGraphics();
    m_button->setGraphics(activeGraphicsCopy);
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
            auto activeGraphicsCopy = child->getGraphics()->clone();
            m_button->freeGraphics();
            m_button->setGraphics(activeGraphicsCopy);
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

    if (!m_opened) return;

    for (auto&[name, child] : m_children)
    {
        child->render(rendSubsys, resSystem, coordStart);
    }
}

} /* gui namespace. */