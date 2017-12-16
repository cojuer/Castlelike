#include "factory__item.h"

#include "parser_item_proto.h"
#include "text_manager.h"

ItemFactory::ItemFactory() :
    m_loader(new JsonLoader()),
    m_parser(new IProtoParser())
{}

bool ItemFactory::load(const std::string& fname)
{
    auto loaded = true;
    loaded = loaded && m_loader->load(fname);
    return loaded;
}

Resource<Item>* ItemFactory::get(ResourceId& id)
{
    if (m_cache.find(id) != m_cache.end())
    {
        auto item = new Item(m_cache.at(id));
        return item;
    }
    
    auto node = m_loader->get(id);
    
    auto resID = id.substr(id.find_last_of("/") != std::string::npos ? 
                           id.find_last_of("/") : 0);
    m_cache[id] = m_parser->parse(resID, *node);
    return (new Item(m_cache.at(id)));
}

ItemFactory::~ItemFactory()
{
    delete(m_loader);
    delete(m_parser);
}
