#include "font_data.h"

namespace gui {

const std::string Font::latoRegular = "Lato-Regular";
const std::string Font::latoBold    = "Lato-Bold";

const uint32_t FontSize::large  = 20;
const uint32_t FontSize::medium = 16;
const uint32_t FontSize::small  = 12;

Font::Font(TTF_Font* font) :
    m_font(font)
{}

Font::operator TTF_Font*() const
{
    return m_font;
}

Font::~Font()
{
    TTF_CloseFont(m_font);
}

}
