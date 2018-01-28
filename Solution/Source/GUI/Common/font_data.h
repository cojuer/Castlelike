#pragma once

#include <string>

#include <SDL_ttf.h>

namespace gui {

class Font
{
public:
    static const std::string latoRegular;
    static const std::string latoBold;

    Font(TTF_Font* font);

    operator TTF_Font*() const;

    ~Font();

private:
    TTF_Font* m_font;
};

struct FontSize
{
    static const uint32_t large;
    static const uint32_t medium;
    static const uint32_t small;
};

} /* gui namespace */