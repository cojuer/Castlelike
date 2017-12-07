#pragma once

#include "vec2.h"

template<typename T>
struct Rect
{
    Rect();
    Rect(T x, T y, T w, T h);

    bool operator==(const Rect<T>& another) const;
    bool operator!=(const Rect<T>& another) const;
    
    bool contains(const Vec2<T>& point) const;
    bool intersects(const Rect<T>& another) const;

    /* members */
    T x, y, w, h;
};

template<typename T>
Rect<T>::Rect() = default;

template<typename T>
Rect<T>::Rect(T x, T y, T w, T h) : 
    x(x), y(y), w(w), h(h) 
{}

template<typename T>
bool Rect<T>::operator==(const Rect<T>& another) const
{
    return x == another.x && y == another.y &&
           w == another.w && h == another.h;
}

template<typename T>
bool Rect<T>::operator!=(const Rect<T>& another) const
{
    return x != another.x || y != another.y ||
           w != another.w || h != another.h;
}

template<typename T>
bool Rect<T>::contains(const Vec2<T>& point) const
{
    return x <= point.x && x + w >= point.x &&
           y <= point.y && y + h >= point.y;
}

template<typename T>
bool Rect<T>::intersects(const Rect<T>& another) const
{
    T left = max(x, another.x);
    T top = max(y, another.y);
    T right = min(x + w, another.x + another.w);
    T bottom = min(y + h, another.y + another.h);
    return left < right && top < bottom;
}

using IRect = Rect<int>;
using URect = Rect<unsigned>;
using FRect = Rect<float>;