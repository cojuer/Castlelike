#include "widget__number.h"

#include <string>

#include "atexture.h"
#include "system__resource.h"
#include "subsystem__render.h"
#include "text_renderer.h"
#include "font_data.h"
#include "color.h"

namespace gui {

NumberWidget::NumberWidget(const std::string& name, Widget* parent, SDL_Rect geometry, bool visible, const int* number) :
    Widget(name, parent, geometry, visible),
    m_number(number)
{}

void NumberWidget::render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem, Vec2i coordStart) const
{
    if (!m_visible) return;
    if (!m_number) return;
    //bad, but rather fast
    std::string strNumber = std::to_string(abs(*m_number));
    auto texture = resSystem.textRenderer->renderTexture(strNumber, Font::latoRegular, 15, Color::white);
    SDL_Rect dstRect = { m_geometry.x + coordStart.x, m_geometry.y + coordStart.y, texture->getWidth(), texture->getHeight() };
    rendSubsys.render(texture, dstRect);
}

void NumberWidget::setData(const int& number)
{
    m_number = &number;
}

void NumberWidget::eraseData()
{
    m_number = nullptr;
}

} /* gui namespace. */