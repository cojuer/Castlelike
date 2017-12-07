#include "text_renderer.h"

#include "atexture.h"
#include "resource_manager.h"
#include "spritesheet.h"
#include "subsystem_render.h"
#include "font_data.h"
#include "color.h"

bool TextRenderer::init(ResourceManager& resManager, RenderSubsystem& rendSubsystem)
{
    m_resManager = &resManager;
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

ATexture* TextRenderer::renderTexture(const std::string& text, const std::string& fontName, int size, Color color, int width)
{
    auto font = getFont(fontName, size);
    if (!font) return nullptr;
    auto newIter = m_textures.find({text, font, color, width});
    if (newIter != m_textures.end())
    {
        return newIter->second;
    }
    else
    {
        auto result = new ATexture();
        result->loadFromText(*m_rendSubsystem, text, this->getFont(fontName, size), color, width);
        m_textures[{text, font, color, width}] = result;
        return result;
    }
}

SprSheet* TextRenderer::renderSprSheet(const std::string& text, const std::string& fontName, int size, int width)
{
    auto& textures = *new std::vector<ATexture*>(5);
    for (auto i = 0; i < 5; ++i)
    {
        textures[i] = renderTexture(text, fontName, size, Color::white);
    }
    return new SprSheet(textures);
}
