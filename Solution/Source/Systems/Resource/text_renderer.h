#pragma once

#include <map>
#include <SDL_ttf.h>

#include "atexture.h"
#include "pugixml.hpp"
#include "spritesheet.h"

class Color;
class ResourceSystem;

struct TextInfo
{
    std::string      text;
    TTF_Font*        font;
    SDL_Color        color;
    int              width;

    bool operator==(const TextInfo& info) const
    {
        return (text.compare(info.text) == 0 &&
                font == info.font &&
                color.r == info.color.r &&
                color.g == info.color.g &&
                color.b == info.color.b &&
                color.a == info.color.a &&
                width == info.width);
    }

    bool operator<(const TextInfo& info) const
    {
        if (text.compare(info.text) < 0)
        {
            return true;
        }
        else if (text.compare(info.text) == 0)
        {
            if (font < info.font)
            {
                return true;
            }
            else if (font == info.font)
            {
                if (width < info.width)
                {
                    return true;
                }
                else 
                {
                    return ((color.r << 16) + (color.g << 8) + (color.b) <
                            (info.color.r << 16) + (info.color.g << 8) + (info.color.b));
                }
            }
        }
        return false;
    }
};

class TextRenderer
{
public:
    TextRenderer() = default;
    bool init(ResourceSystem& resSystem, RenderSubsystem& rendSubsystem);

    TTF_Font* getFont(const std::string&, int size);
    ATexture* renderTexture(const std::string& text, const std::string& fontName, int size, Color color, int width = 0);
    SprSheet* renderSprSheet(const std::string& text, const std::string& fontName, int size, int width);

private:
    ResourceSystem* m_resSystem;
    RenderSubsystem* m_rendSubsystem;

    std::map<std::pair<std::string, int>, TTF_Font*> m_fonts;
    std::map<TextInfo, ATexture*>                m_textures;
};