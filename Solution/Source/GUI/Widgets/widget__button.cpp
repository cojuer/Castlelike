#include "widget__button.h"

#include <cassert>

#include "GUI/Behaviour/behaviour.h"
#include "on_release.h"
#include "spritesheet.h"

namespace gui {

Button::Button(Widget* parent) :
    Widget(parent), 
    m_event(nullptr)
{}

Button::Button(const std::string& name, Widget* parent, SDL_Rect geometry, bool visible, Renderable* sprSheet, Event* event) :
    Widget(name, parent, geometry, visible),
    m_event(event)
{
    if (sprSheet)
    {
        setGraphics(sprSheet);
    }

    setBhvr({ new OnRelease(event) });
}

void Button::setGraphics(Renderable* rendered)
{
    if (!rendered) return;
    auto sprSheet = dynamic_cast<SprSheet*>(rendered);
    m_rendered = rendered;
    if (sprSheet)
    {
        m_geometry.w = sprSheet->getWidth();
        m_geometry.h = sprSheet->getHeight();
    }
}

bool Button::handle(SDL_Event& event, Vec2i coordStart)
{
    if (!m_visible) return false;

    if (m_bhvr)
    {
        m_bhvr->behave(event, coordStart);
    }
    return true;
}

void Button::render(RenderSubsystem& rendSubsystem, ResourceSystem& resSystem, Vec2i coordStart) const
{
    if (!m_visible) return;

    if (m_rendered)
    {
        dynamic_cast<SprSheet*>(m_rendered)->setFrame(static_cast<int>(m_state));
    }

    renderSelf(rendSubsystem, resSystem, coordStart);
    renderText(rendSubsystem, resSystem, coordStart);
}

void Button::loadGraphics(Json& node, ResourceSystem& resSystem)
{
    Widget::loadGraphics(node, resSystem);
    assert(!m_rendered || dynamic_cast<SprSheet*>(m_rendered));
    //setGraphics(dynamic_cast<SprSheet*>(m_rendered));
}

} /* gui namespace. */
