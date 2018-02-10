#include "tile.h"

Tile::Tile(std::string tileset, 
           uint32_t id, 
           Renderable* view, 
           bool collisive) :
    m_tileset(std::move(tileset)),
    m_id(id),
    m_view(view),
    m_collisive(collisive)
{}

uint32_t Tile::getID() const
{
    return m_id;
}

std::string Tile::getTileset() const
{
    return m_tileset;
}

Renderable* Tile::getView() const
{
    return m_view.get();
}

bool Tile::isCollisive() const
{
	return m_collisive;
}
