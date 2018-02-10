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

    Font(const Font&) = delete;
    Font(Font&&) = delete;
    Font& operator=(const Font&) = delete;
    Font& operator=(Font&&) = delete;

    ~Font();

    operator TTF_Font*() const;

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