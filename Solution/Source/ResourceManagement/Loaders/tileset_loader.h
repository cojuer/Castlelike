#pragma once

#include "loader.h"
#include "pugi_aliases.h"
#include "tileset.h"

struct CharProto;
class ResourceManager;

class TilesetLoader : public Loader<Tileset*>
{
public:
	TilesetLoader();

	bool init(ResourceManager& resManager);

	bool             load(const std::string& fname) override;
	bool             has(ResourceId& id) override;
	Tileset*         get(ResourceId& id) override;

private:
	ResourceManager* m_resManager;
	PugiDoc          m_parseResult;
};