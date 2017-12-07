#pragma once

#include <SDL.h>

class Color
{
public:
    static const Color white;
    static const Color silver;

    Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 0);

    void getRGB(uint8_t* r, uint8_t* g = nullptr, uint8_t* b = nullptr, uint8_t* a = nullptr) const;

    operator SDL_Color() const;

private:
    uint8_t m_r;
    uint8_t m_g;
    uint8_t m_b;
    uint8_t m_a;
};