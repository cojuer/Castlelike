#include "tileset_loader.h"

#include <cassert>
#include <iostream>

#include "resource_manager.h"

TilesetLoader::TilesetLoader() : 
    m_resManager(nullptr)
{}

bool TilesetLoader::init(ResourceManager& resManager)
{
	m_resManager = &resManager;
	return true;
}

bool TilesetLoader::load(const std::string& fname)
{
	auto result = m_parseResult.load_file(fname.c_str());

	if (result)
	{
		std::cout << "Tileset loader: " << fname << " successfully loaded" << std::endl;
		return true;
	}
	return false;
}

bool TilesetLoader::has(ResourceId& id)
{
	auto protoNode = m_parseResult.child("itemDB").find_child_by_attribute("id", id.c_str());
	return protoNode;
}

Tileset* TilesetLoader::get(ResourceId& id)
{
	auto tilesetNode = m_parseResult.child("tilesetDB").find_child_by_attribute("id", id.c_str());
	auto& tileset = *new Tileset();
	tileset.m_columns = tilesetNode.attribute("columns").as_int();
	tileset.m_tileWidth = tilesetNode.attribute("tilewidth").as_int();
	tileset.m_tileHeight = tilesetNode.attribute("tileheight").as_int();
	tileset.m_margin = tilesetNode.attribute("margin").as_int();
	tileset.m_spacing = tilesetNode.attribute("spacing").as_int();
	tileset.m_image = m_resManager->get<Renderable>(tilesetNode.attribute("id").as_string());
	return &tileset;
}
