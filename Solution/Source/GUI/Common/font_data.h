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
    static const int large;
    static const int medium;
    static const int small;
};

} /* gui namespace */