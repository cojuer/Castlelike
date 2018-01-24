#include "parser__tileset.h"

#include "system__resource.h"

#include "renderable.h"
#include "tile.h"

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
        tset->m_terrains[terr.m_name] = std::move(terr);
    }

    std::vector<std::string> tileTerrs(tset->m_cols * tset->m_rows);
    for (const auto&[terrName, terrain] : tset->m_terrains)
    {
        for (auto id : terrain.m_tiles)
        {
            tileTerrs[id] = terrain.m_name;
        }
    }
    tset->m_tileTerrs = tileTerrs;

    std::vector<std::unique_ptr<ATexture>> tileTextures{ tset->m_cols * tset->m_rows };
    for (uint32_t id = 0; id != tset->m_cols * tset->m_rows; ++id)
    {
        auto view = new ATexture(*tset->m_image);
        auto x = tset->m_margin + id % tset->m_cols * (tset->m_tileW + tset->m_spacing);
        auto y = tset->m_margin + id / tset->m_cols * (tset->m_tileH + tset->m_spacing);
        SDL_Rect src{ x, y, tset->m_tileW, tset->m_tileH };
        view->setSrcRect(src);
        tileTextures[id].reset(view);
    }
    tset->m_tileTextures = std::move(tileTextures);

    for (uint32_t id = 0; id != tset->m_cols * tset->m_rows; ++id)
    {
        auto view = tset->m_tileTextures.at(id).get();
        auto collision = tset->m_terrains.at(tset->m_tileTerrs.at(id)).m_collisive;
        tset->m_tiles.emplace_back( tset, id, view, collision );
    }
    return tset;
}
