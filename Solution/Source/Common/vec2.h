#pragma once

#include "direction.h"

template<typename T>
struct Vec2
{
    Vec2();
    Vec2(T x, T y);

    explicit Vec2(const Direction dir);

    Vec2<T> operator+(const Vec2<T>& another) const;
    Vec2<T> operator-(const Vec2<T>& another) const;
    Vec2<T> operator*(const int multiplier) const;

    Vec2<T>& operator+=(const Vec2<T>& another);
    Vec2<T>& operator-=(const Vec2<T>& another);

    bool operator==(const Vec2<T>& another) const;
    bool operator!=(const Vec2<T>& another) const;
    bool operator<(const Vec2<T>& another) const;

    /* members */
    T x, y;
};

template<typename T>
Vec2<T>::Vec2() = default;

template<typename T>
Vec2<T>::Vec2(T x, T y) : x(x), y(y) {}

template<typename T>
Vec2<T>::Vec2(const Direction dir) : x(0), y(0)
{
    switch (dir)
    {
    case Direction::UPWARD:    y = -1; break;
    case Direction::DOWNWARD:  y = 1;  break;
    case Direction::LEFTWARD:  x = -1; break;
    case Direction::RIGHTWARD: x = 1;  break;
    default: break;
    }
}

template<typename T>
Vec2<T> Vec2<T>::operator+(const Vec2<T>& another) const
{
    Vec2<T> result;
    result.x = x + another.x;
    result.y = y + another.y;
    return result;
}

template<typename T>
Vec2<T> Vec2<T>::operator-(const Vec2<T>& another) const
{
    Vec2<T> result;
    result.x = x - another.x;
    result.y = y - another.y;
    return result;
}

template<typename T>
Vec2<T> Vec2<T>::operator*(const int multiplier) const
{
    Vec2<T> result;
    result.x = x * multiplier;
    result.y = y * multiplier;
    return result;
}

template<typename T>
Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& another)
{
    x += another.x;
    y += another.y;
    return *this;
}

template<typename T>
Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& another)
{
    x -= another.x;
    y -= another.y;
    return *this;
}

template<typename T>
bool Vec2<T>::operator==(const Vec2<T>& another) const
{
    return (x == another.x && y == another.y);
}

template<typename T>
bool Vec2<T>::operator!=(const Vec2<T>& another) const
{
    return (x != another.x || y != another.y);
}

template<typename T>
bool Vec2<T>::operator<(const Vec2<T>& another) const
{
    return (x < another.x || (x == another.x && y < another.y));
}

using Coord = Vec2<int>;
using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;
