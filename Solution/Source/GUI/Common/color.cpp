#include "color.h"

const Color Color::white =  Color{ 255, 255, 255 };
const Color Color::silver = Color{ 186, 186, 186 };

Color::Color(uint8_t r, uint8_t  g, uint8_t b, uint8_t a) :
    m_r(r),
    m_g(g),
    m_b(b),
    m_a(a)
{}

void Color::getRGB(uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const
{
    if (r) *r = m_r;
    if (g) *g = m_g;
    if (b) *b = m_b;
    if (a) *a = m_a;
}

Color::operator SDL_Color() const
{
    return { m_r, m_g, m_b, m_a };
}