#include "widget__tabs.h"

#include "widget__button.h"

namespace gui {

TabWidget::TabWidget(const std::string& name, Widget* parent, int x, int y, int width, int height, bool visible, Renderable* rendered) :
    Widget(name, parent, {x, y, width, height}, visible), 
    m_activeTabNum(0)
{
    m_rendered = rendered;
}

void TabWidget::addTab(Button& button, Widget& panel)
{
    // TODO: check name collisions
    m_tabs.push_back({ &button, &panel });
    addChild(button);
    addChild(panel);
}

bool TabWidget::handle(SDL_Event& event, Vec2i coordStart)
{
    if (!m_visible) return false;

    coordStart += getPos();

    for (size_t i = 0; i < m_tabs.size(); ++i)
    {
        auto button = m_tabs[i].first;
        button->handle(event, coordStart);
        auto state = button->getState();
        if (state == WState::PRESSED ||
            state == WState::PRESSED_MOUSE_OUT)
        {
            m_activeTabNum = i;
            break;
        }
    }
    m_tabs[m_activeTabNum].second->handle(event, coordStart);
    return true;
}

void TabWidget::render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem, Vec2i coordStart) const
{
    if (!m_visible) return;

    coordStart += getPos();

    for (auto& element : m_tabs)
    {
        element.first->render(rendSubsys, resSystem, coordStart);
    }
    m_tabs[m_activeTabNum].second->render(rendSubsys, resSystem, coordStart);
}

} /* gui namespace. */