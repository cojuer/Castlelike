#pragma once

#include <string>

#include "gui_text_style.h"

inline bool operator==(const SDL_Color& lhs, const SDL_Color& rhs)
{
    return std::tie(lhs.r, lhs.g, lhs.b, lhs.a) ==
           std::tie(rhs.r, rhs.g, rhs.b, rhs.a);
}

inline bool operator<(const SDL_Color& lhs, const SDL_Color& rhs)
{
    return std::tie(lhs.r, lhs.g, lhs.b, lhs.a) <
           std::tie(rhs.r, rhs.g, rhs.b, rhs.a);
}

namespace gui {

struct GUIText
{
    TextStyle   m_style;
    std::string m_text;

    bool operator==(const GUIText& rhs) const
    {
        return std::tie(m_text, m_style) ==
               std::tie(rhs.m_text, rhs.m_style);
    }

    bool operator<(const GUIText& rhs) const
    {
        return std::tie(m_text, m_style) <
               std::tie(rhs.m_text, rhs.m_style);
    }
};

} /* gui namespace */