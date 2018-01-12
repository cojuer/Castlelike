#include "room.h"
#include "rng.h"

RoomModel::RoomModel(Coord leftTop, unsigned int width, unsigned int height) :
    m_leftTop(leftTop),
    m_width(width),
    m_height(height)
{}

Coord RoomModel::getLeftTopCoord() const
{
    return m_leftTop;
}

unsigned int RoomModel::getWidth() const
{
    return m_width;
}

unsigned int RoomModel::getHeight() const
{
    return m_height;
}

unsigned int RoomModel::getSquare() const
{
    return m_width * m_height;
}

Coord RoomModel::getRandomWallTile(Direction dir) const
{
    RNG rng{ 0 };
    Coord result;
    switch (dir)
    {
    case Direction::UPWARD:
        result.y = m_leftTop.y;
        result.x = m_leftTop.x + rng.getFrom(1, m_width - 2);
        break;
    case Direction::LEFTWARD:
        result.x = m_leftTop.x;
        result.y = m_leftTop.y + rng.getFrom(1, m_height - 2);
        break;
    case Direction::DOWNWARD:
        result.y = m_leftTop.y + m_height - 1;
        result.x = m_leftTop.x + rng.getFrom(1, m_width - 2);
        break;
    case Direction::RIGHTWARD:
        result.x = m_leftTop.x + m_width - 1;
        result.y = m_leftTop.y + rng.getFrom(1, m_height - 2);
        break;
    default:
        result = { 0, 0 };
    }
    return result;
}