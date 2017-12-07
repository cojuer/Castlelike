#include "tileset_factory.h"

#include "text_manager.h"
#include "tileset_loader.h"

TilesetFactory::TilesetFactory() :
	m_loader(new TilesetLoader())
{}

bool TilesetFactory::init(ResourceManager& resManager)
{
	auto inited = true;
	inited = inited && m_loader->init(resManager);
	return inited;
}

bool TilesetFactory::load(const std::string& fname)
{
	auto loaded = true;
	loaded = loaded && m_loader->load(fname);
	return loaded;
}

Resource<Tileset>* TilesetFactory::get(ResourceId& id)
{
	if (m_cache.find(id) != m_cache.end())
	{
		return &m_cache.at(id);
	}

	auto tileset = m_loader->get(id);
    if (tileset)
    {
        m_cache[id] = *tileset;
    }
	return tileset;
}

TilesetFactory::~TilesetFactory()
{
    delete(m_loader);
}
