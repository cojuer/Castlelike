#include "widget__text_holder.h"

#include "atexture.h"
#include "resource_manager.h"
#include "subsystem_render.h"
#include "text_renderer.h"

namespace gui {

TextOwnerWidget::TextOwnerWidget(const std::string& name, Widget* parent, SDL_Rect geometry, bool visible, TextRenderInfo rendInfo) :
    Widget(name, parent, geometry, visible),
    m_rendInfo(rendInfo),
    m_text("")
{}

void TextOwnerWidget::setTextRendInfo(TextRenderInfo rendInfo)
{
    m_rendInfo = rendInfo;
}

void TextOwnerWidget::setText(const std::string& text)
{
    m_text = text;
}

void TextOwnerWidget::render(RenderSubsystem& rendSubsys, ResourceManager& resManager, Vec2i coordStart) const
{
    auto texture = resManager.textRenderer->renderTexture(m_text, m_rendInfo.m_font, m_rendInfo.m_fontSize, m_rendInfo.m_color, m_geometry.w);
    SDL_Rect dstRect = { 
        m_geometry.x + coordStart.x,
        m_geometry.y + coordStart.y,
        texture->getWidth(),
        texture->getHeight() 
    };
    rendSubsys.render(texture, dstRect);
}

} /* gui namespace */