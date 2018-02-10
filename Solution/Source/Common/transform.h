#pragma once

#include "vec2.h"

struct Transform
{
    Vec2i m_shift { 0, 0 };
    float m_angle { 0 };
    float m_scale { 1 };
};