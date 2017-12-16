#include "factory__newarea.h"

#include <iostream>
#include <sstream>

#include "atexture.h"
#include "renderable.h"
#include "resource_manager.h"
#include "tile.h"
#include "tileset.h"
#include "factory__tileset.h"

bool NewSceneFactory::init(ResourceManager& resManager)
{
    m_resManager = &resManager;
    return true;
}

bool NewSceneFactory::load(const std::string& fname)
{
	bool loaded = true;
    loaded = loaded && m_parseResult.load_file(fname.c_str());
	
    if (loaded)
    {
        std::cout << "Scenes data loaded" << std::endl;
    }
    return loaded;
}

Resource<Scene>* NewSceneFactory::get(ResourceId& id)
{
    auto areaNode = m_parseResult.child("areaDB").find_child_by_attribute("res", id.c_str());
    auto width = areaNode.attribute("width").as_int();
    auto height = areaNode.attribute("height").as_int();
	std::vector<std::pair<int, Tileset>> tilesets;
	auto tilesetsNode = areaNode.child("tilesets");
	for (auto tileset = tilesetsNode.child("tileset"); tileset; tileset = tileset.next_sibling("tileset"))
	{
		auto tset = m_resManager->m_tilesetFactory->get(tileset.attribute("id").as_string());
		auto gid = tileset.attribute("firstgid").as_int();
		tilesets.push_back({ gid, *tset });
	}

    auto tiles = new std::vector<std::vector<Tile*>>();

    auto dataNode = areaNode.child("data");
    for (auto rowNode = dataNode.child("row"); rowNode; rowNode = rowNode.next_sibling("row") )
    {
        std::vector<Tile*> row;
        std::string rowData = rowNode.attribute("data").as_string();
        auto idData = split(rowData, ',');
        for (auto& someID : idData)
        {
			for (size_t i = 0; i < tilesets.size(); ++i)
			{
				if (tilesets[i].first <= someID && i + 1 == tilesets.size() ||
					tilesets[i].first <= someID && tilesets[i + 1].first > someID)
				{
					auto offset = someID - tilesets[i].first;
					auto tileset = tilesets[i].second;
					SDL_Rect src{ 
						tileset.m_margin + offset % tileset.m_columns * (tileset.m_spacing + tileset.m_tileWidth),
						tileset.m_margin + offset / tileset.m_columns * (tileset.m_spacing + tileset.m_tileHeight),
						tileset.m_tileWidth,
						tileset.m_tileHeight
					};
					auto texture = tileset.m_image->clone();
					texture->getTexture()->setSrcRect(src);
					row.push_back(new Tile{ texture, false });
				}
			}
        }
        tiles->push_back(row);
    }
    return new Scene("new_epoch", *tiles, std::vector<Actor*>());
}

std::vector<int> NewSceneFactory::split(const std::string &s, char delim) const
{
    std::stringstream ss{ s };
    std::string item;
    std::vector<int> result;
    while (std::getline(ss, item, delim)) 
    {
        result.push_back(std::stoi(item));
    }
    return result;
}
