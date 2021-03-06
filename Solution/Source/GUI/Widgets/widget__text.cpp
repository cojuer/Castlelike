#include "widget__text.h"

#include "atexture.h"
#include "system__resource.h"
#include "subsystem__render.h"
#include "text_renderer.h"

namespace gui {

TextWidget::TextWidget(const std::string& name, Widget* parent, SDL_Rect geometry, bool visible, const std::string& fName, int fSize, Color color, const std::string* text) :
    Widget(name, parent, geometry, visible),
    fName(fName),
    fSize(fSize),
    color(color),
    text(text)
{}

/* wow, the worst render function ever */
void TextWidget::render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem, Vec2i coordStart) const
{
    auto texture = resSystem.textRenderer->renderTexture(*text, fName, fSize, color, m_geometry.w);
    SDL_Rect dstRect = { m_geometry.x + coordStart.x, 
                         m_geometry.y + coordStart.y, 
                         texture->getWidth(), 
                         texture->getHeight() };
    rendSubsys.render(texture, dstRect);
}

} /* gui namespace. */