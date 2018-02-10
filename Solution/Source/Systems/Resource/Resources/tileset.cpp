#include "tileset.h"

#include "tile.h"

Tileset::Tileset(ResourceId id,
                 std::map<std::string, Terrain>&& terrains,
                 std::vector<Tile>&& tiles) :
    m_resID(id),
    m_terrains(std::move(terrains)),
    m_tiles(std::move(tiles))
{}

ResourceId Tileset::getResID() const
{
    return m_resID;
}

Tileset::Terrain Tileset::getTerrain(const std::string& name) const
{
    return m_terrains.at(name);
}

Tile* Tileset::getTile(uint32_t id)
{
    return &m_tiles.at(id);
}

uint32_t Tileset::getSize() const
{
    return m_tiles.size();
}
