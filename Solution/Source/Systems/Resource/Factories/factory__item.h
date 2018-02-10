#pragma once

#include <map>

#include "item.h"
#include "factory.h"
#include "pugi_aliases.h"
#include "resource.h"
#include "loader__json.h"
#include "parser__item_proto.h"

class ItemFactory : public Factory<Item>
{
    using ItemCache   = std::map<std::string, Resource<std::shared_ptr<const ItemProto>>>;

public:
    ItemFactory() = default;

    bool      load(const std::string& fname) override;
    Resource<Item>* get(ResourceId& id) override;

private:
    JsonLoader      m_loader;
    PugiDoc         m_parseResult;
    IProtoParser    m_parser;
    ItemCache       m_cache;
};