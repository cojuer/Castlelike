#pragma once

#include <map>

#include "factory.h"
#include "resource.h"
#include "tileset.h"
#include "loader__json.h"
#include "parser__tileset.h"

class ResourceSystem;

class TilesetFactory : public Factory<Tileset>
{
	using TilesetCache = std::map<std::string, Tileset*>;

public:
	TilesetFactory() = default;

	bool init(ResourceSystem& resSystem);

	bool      load(const std::string& fname) override;
	Resource<Tileset>* get(ResourceId& id) override;

private:
    JsonLoader    m_loader;
	TilesetParser m_parser;
	TilesetCache  m_cache;
};