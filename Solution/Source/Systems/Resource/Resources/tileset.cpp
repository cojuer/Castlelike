#include "tileset.h"

#include "tile.h"

Tileset::Tileset(ResourceId id) :
    m_resID(id)
{}

Tile* Tileset::getTile(uint32_t id)
{
    return &m_tiles.at(id);
}