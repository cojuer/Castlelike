#pragma once

#include <map>
#include <SDL_ttf.h>

#include "atexture.h"
#include "pugixml.hpp"
#include "spritesheet.h"

#include "gui_text_style.h"
#include "gui_text.h"

class Color;
class ResourceSystem;

class TextRenderer
{
public:
    TextRenderer() = default;
    bool init(ResourceSystem& resSystem, RenderSubsystem& rendSubsystem);

    TTF_Font* getFont(const std::string&, int size);
    ATexture* renderTexture(const std::string& text, const std::string& fontName, uint32_t size, Color color, uint32_t width = 0);
    ATexture* renderTexture(const std::string& text, gui::TextStyle style);
    SprSheet* renderSprSheet(const std::string& text, const std::string& fontName, int size, int width);
    
private:
    ResourceSystem*  m_resSystem { nullptr };
    RenderSubsystem* m_rendSubsystem { nullptr };

    std::map<std::pair<std::string, int>, TTF_Font*> m_fonts;
    std::map<gui::GUIText, ATexture*>                m_textures;
};