#include "parser__tileset.h"

#include "system__resource.h"

#include "renderable.h"

TilesetParser::TilesetParser() = default;

bool TilesetParser::init(ResourceSystem& resSystem)
{
    m_resSystem = &resSystem;
    return true;
}

Tileset* TilesetParser::parse(const std::string& nodeName, Json& node)
{
    auto tset = new Tileset{ nodeName };

    tset->m_image = dynamic_cast<ATexture*>(m_resSystem->get<Renderable>(node.at("image").get<std::string>()));

    tset->m_rows = node.at("rows");
    tset->m_cols = node.at("cols");

    tset->m_spacing = node.at("spacing");
    tset->m_margin = node.at("margin");

    tset->m_tileW = node.at("tileW");
    tset->m_tileH = node.at("tileH");

    auto terrainsNode = node.at("terrains");
    for (auto it = terrainsNode.begin(); it != terrainsNode.end(); ++it)
    {
        auto terrName = it.key();
        auto terrDict = it.value();
        auto collisive = terrDict.at("collisive").get<bool>();
        auto tiles = terrDict.at("tiles").get<std::vector<uint32_t>>();

        Tileset::Terrain terr{ terrName, collisive, tiles };
        tset->m_terrains[terr.m_name] = terr;
    }

    std::vector<std::string> tileTerrs(tset->m_cols * tset->m_rows);
    for (const auto& pair : tset->m_terrains)
    {
        auto terrain = pair.second;
        for (auto id : terrain.m_tiles)
        {
            tileTerrs[id] = terrain.m_name;
        }
    }
    tset->m_tileTerrs = tileTerrs;

    return tset;
}
