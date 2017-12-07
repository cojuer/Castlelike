#include "tile.h"

Tile::Tile(Renderable* view, bool collisive) :
    m_view(view),
    m_collisive(collisive)
{}

Renderable* Tile::getView() const
{
    return m_view;
}

bool Tile::isCollisive() const
{
	return m_collisive;
}