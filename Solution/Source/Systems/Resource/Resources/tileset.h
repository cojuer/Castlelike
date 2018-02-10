#pragma once

#include <map>
#include <vector>

#include "resource_id.h"

class Tile;

class Tileset
{
public:
    struct Terrain
    {
        std::string m_name;
        bool m_collisive;
        std::vector<uint32_t> m_tiles;
    };

    Tileset(ResourceId id, 
            std::map<std::string, Terrain>&& terrains,
            std::vector<Tile>&& tiles);

    ResourceId getResID() const;
    Terrain    getTerrain(const std::string& name) const;
    Tile*      getTile(uint32_t id);
    uint32_t   getSize() const;

private:
    ResourceId m_resID;
    std::map<std::string, Terrain> m_terrains;
    std::vector<Tile> m_tiles;
};