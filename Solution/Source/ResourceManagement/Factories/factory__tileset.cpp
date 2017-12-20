#include "factory__tileset.h"

#include "text_manager.h"
#include "loader__json.h"
#include "parser__tileset.h"

TilesetFactory::TilesetFactory() :
	m_loader(new JsonLoader()),
    m_parser(new TilesetParser())
{}

bool TilesetFactory::init(ResourceManager& resManager)
{
	auto inited = true;
    inited = inited && m_parser->init(resManager);
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

	auto tsetNode = m_loader->get(id);
    if (!tsetNode) return nullptr;
    
    auto tset = m_parser->parse(id, *tsetNode);
	return tset;
}

TilesetFactory::~TilesetFactory()
{
    delete(m_loader);
}
