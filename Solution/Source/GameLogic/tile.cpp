#include "tile.h"

#include "tileset.h"

Tile::Tile(Tileset* tileset, 
           uint32_t id, 
           Renderable* view, 
           bool collisive) :
    m_tileset(tileset),
    m_id(id),
    m_view(view),
    m_collisive(collisive)
{}

Tile::Tile(Renderable* view, bool collisive) :
    m_view(view),
    m_collisive(collisive)
{}

uint32_t Tile::getID() const
{
    return m_id;
}

Tileset* Tile::getTileset() const
{
    return m_tileset;
}

Renderable* Tile::getView() const
{
    return m_view;
}

bool Tile::isCollisive() const
{
	return m_collisive;
}