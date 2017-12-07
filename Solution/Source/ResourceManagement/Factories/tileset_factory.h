#pragma once

#include <map>

#include "item.h"
#include "factory.h"
#include "pugi_aliases.h"
#include "resource.h"
#include "tileset.h"

class ResourceManager;
class TilesetLoader;

class TilesetFactory : public Factory<Tileset>
{
	using TilesetCache = std::map<std::string, Resource<Tileset>>;

public:
	TilesetFactory();

	bool init(ResourceManager& resManager);

	bool      load(const std::string& fname) override;
	Resource<Tileset>* get(ResourceId& id) override;

    ~TilesetFactory();

private:
	PugiDoc          m_parseResult;
	TilesetLoader*   m_loader;
	TilesetCache     m_cache;
};