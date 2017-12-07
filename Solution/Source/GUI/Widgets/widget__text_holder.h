#pragma once

#include "widget.h"
#include "color.h"

namespace gui {

struct TextRenderInfo
{
    std::string m_font;
    int m_fontSize;
    Color m_color;
};

class TextOwnerWidget : public Widget
{
public:
    TextOwnerWidget(const std::string& name,
                    Widget* parent,
                    SDL_Rect geometry,
                    bool visible,
                    TextRenderInfo rendInfo);

    void setTextRendInfo(TextRenderInfo rendInfo);
    void setText(const std::string& text);

    void render(RenderSubsystem& rendSubsys,
                ResourceManager& resManager,
                Vec2i coordStart = { 0, 0 }) const override;

private:
    TextRenderInfo m_rendInfo;
    std::string    m_text;
};

} /* gui namespace */
