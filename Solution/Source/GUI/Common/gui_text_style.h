#pragma once

#include <tuple>

#include "font_data.h"
#include "color.h"

namespace gui {

struct TextStyle
{
    TextStyle(std::string font = gui::Font::latoRegular, 
              uint32_t fontSize = gui::FontSize::medium,
              SDL_Color color = Color::silver,
              uint32_t width = 0) :
        m_font(std::move(font)),
        m_fontSize(fontSize),
        m_color(color),
        m_width(width)
    {}

    std::string m_font;
    uint32_t    m_fontSize;
    SDL_Color   m_color;
    uint32_t    m_width;

    bool operator==(const TextStyle& rhs) const
    {
        return std::tie(m_font, m_fontSize, m_color, m_width) ==
               std::tie(rhs.m_font, rhs.m_fontSize, rhs.m_color, rhs.m_width);
    }

    bool operator<(const TextStyle& rhs) const
    {
        return std::tie(m_font, m_fontSize, m_color, m_width) <
               std::tie(rhs.m_font, rhs.m_fontSize, rhs.m_color, rhs.m_width);
    }
};

} /* gui namespace */