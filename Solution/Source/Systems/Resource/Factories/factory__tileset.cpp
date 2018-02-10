#include "factory__tileset.h"

#include "text_manager.h"
#include "loader__json.h"
#include "parser__tileset.h"

bool TilesetFactory::init(ResourceSystem& resSystem)
{
	auto inited = true;
    inited = inited && m_parser.init(resSystem);
	return inited;
}

bool TilesetFactory::load(const std::string& fname)
{
	auto loaded = true;
	loaded = loaded && m_loader.load(fname);
	return loaded;
}

Resource<Tileset>* TilesetFactory::get(ResourceId& id)
{
	if (m_cache.find(id) != m_cache.end())
	{
		return m_cache.at(id);
	}

	auto tsetNode = m_loader.get(id);
    if (!tsetNode) return nullptr;
    
    auto tset = m_parser.parse(id, *tsetNode);
    if (tset)
    {
        m_cache[id] = tset;
    }
	return tset;
}
