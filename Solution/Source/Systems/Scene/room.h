#pragma once

#include "vec2.h"

class RoomModel
{
public:
    RoomModel(Coord leftTop, unsigned int width, unsigned int height);

    Coord getLeftTopCoord() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    unsigned int getSquare() const;

    Coord getRandomWallTile(Direction dir) const;

private:
    Coord m_leftTop;
    unsigned m_width;
    unsigned m_height;
};