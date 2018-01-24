#pragma once

#include <map>
#include <memory>
#include <vector>

#include "renderable.h"
#include "resource_id.h"
#include "atexture.h"

class Tile;
class Renderable;

struct Tileset
{
    Tileset(ResourceId id);
    Tile* getTile(uint32_t id);

    struct Terrain
    {
        std::string m_name;
        bool m_collisive;
        std::vector<uint32_t> m_tiles;
    };

    ResourceId m_resID;
	ATexture* m_image;
    uint32_t m_rows;
    uint32_t m_cols;
    uint32_t m_tileW;
    uint32_t m_tileH;
	uint8_t m_margin;
	uint8_t m_spacing;
    std::map<std::string, Terrain> m_terrains;
    std::vector<std::unique_ptr<ATexture>> m_tileTextures;
    std::vector<Tile> m_tiles;
    std::vector<std::string> m_tileTerrs;
};