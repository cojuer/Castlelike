#pragma once

#include <map>

#include "factory.h"
#include "resource.h"
#include "tileset.h"

class JsonLoader;
class ResourceManager;
class TilesetParser;

class TilesetFactory : public Factory<Tileset>
{
	using TilesetCache = std::map<std::string, Tileset>;

public:
	TilesetFactory();

	bool init(ResourceManager& resManager);

	bool      load(const std::string& fname) override;
	Resource<Tileset>* get(ResourceId& id) override;

    ~TilesetFactory();

private:
    JsonLoader*    m_loader;
	TilesetParser* m_parser;
	TilesetCache   m_cache;
};