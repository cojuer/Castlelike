#include "parser__tileset.h"

#include "system__resource.h"

#include "atexture.h"
#include "renderable.h"
#include "tile.h"

bool TilesetParser::init(ResourceSystem& resSystem)
{
    m_resSystem = &resSystem;
    return true;
}

Tileset* TilesetParser::parse(const std::string& nodeName, Json& node)
{
    auto image = dynamic_cast<ATexture*>(m_resSystem->get<Renderable>(node.at("image").get<std::string>()));

    auto rows = node.at("rows").get<uint32_t>();
    auto cols = node.at("cols").get<uint32_t>();

    auto spacing = node.at("spacing").get<uint32_t>();
    auto margin = node.at("margin").get<uint32_t>();

    auto tileW = node.at("tileW").get<uint32_t>();
    auto tileH = node.at("tileH").get<uint32_t>();

    auto terrainsNode = node.at("terrains");
    std::map<std::string, Tileset::Terrain> terrains;
    for (auto it = terrainsNode.begin(); it != terrainsNode.end(); ++it)
    {
        auto terrName = it.key();
        auto terrDict = it.value();
        auto collisive = terrDict.at("collisive").get<bool>();
        auto tiles = terrDict.at("tiles").get<std::vector<uint32_t>>();

        Tileset::Terrain terr{ terrName, collisive, tiles };
        terrains[terr.m_name] = std::move(terr);
    }

    std::vector<std::string> tileTerrs(cols * rows);
    for (const auto&[terrName, terrain] : terrains)
    {
        for (auto id : terrain.m_tiles)
        {
            tileTerrs[id] = terrain.m_name;
        }
    }

    std::vector<Tile> tiles;
    for (uint32_t id = 0; id != cols * rows; ++id)
    {
        auto view = new ATexture(*image);
        auto x = margin + id % cols * (tileW + spacing);
        auto y = margin + id / cols * (tileH + spacing);
        view->setSrcRect({ int32_t(x), int32_t(y), int32_t(tileW), int32_t(tileH) });
        auto collision = terrains.at(tileTerrs.at(id)).m_collisive;
        tiles.emplace_back( nodeName, id, view, collision );
    }

    auto tset = new Tileset{ nodeName, std::move(terrains), std::move(tiles) };
    return tset;
}
