#include "text_renderer.h"

#include "atexture.h"
#include "system__resource.h"
#include "spritesheet.h"
#include "subsystem__render.h"
#include "font_data.h"
#include "color.h"

bool TextRenderer::init(ResourceSystem& resSystem, RenderSubsystem& rendSubsystem)
{
    m_resSystem = &resSystem;
    m_rendSubsystem = &rendSubsystem;
    return true;
}

TTF_Font* TextRenderer::getFont(const std::string& name, int size)
{
    auto iter = m_fonts.find(std::make_pair(name, size));
    if (iter != m_fonts.end())
    {
        return iter->second;
    }
    else
    {
        TTF_Font* font = TTF_OpenFont(("Assets\\Fonts\\" + name + ".ttf").c_str(), size);
        m_fonts[std::make_pair(name, size)] = font;
        return font;
    }
}

ATexture* TextRenderer::renderTexture(const std::string& text, const std::string& fontName, uint32_t size, Color color, uint32_t width)
{
    auto newIter = m_textures.find({ { fontName, size, color, width }, text });
    if (newIter != m_textures.end())
    {
        return newIter->second;
    }
    else
    {
        auto result = new ATexture();
        result->loadFromText(*m_rendSubsystem, text, this->getFont(fontName, size), color, width);
        m_textures[{ { fontName, size, color, width }, text }] = result;
        return result;
    }
}

ATexture* TextRenderer::renderTexture(const std::string& text, gui::TextStyle style)
{
    auto iter = m_textures.find({ style, text });
    if (iter != m_textures.end())
    {
        return iter->second;
    }
    else
    {
        auto result = new ATexture();
        auto font = m_resSystem->textRenderer->getFont(style.m_font, style.m_fontSize);
        result->loadFromText(*m_rendSubsystem, text, font, style.m_color, style.m_width);
        m_textures[{ style, text }] = result;
        return result;
    }
}

SprSheet* TextRenderer::renderSprSheet(const std::string& text, const std::string& fontName, int size, int width)
{
    std::vector<ATexture*> textures{ 5 };
    for (auto i = 0; i < 5; ++i)
    {
        textures[i] = renderTexture(text, fontName, size, Color::white);
    }
    return new SprSheet(std::move(textures));
}
