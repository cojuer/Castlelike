#pragma once

#include <map>
#include <memory>

#include "json_aliases.h"
#include "resource_id.h"

class JsonLoader
{
public:
    JsonLoader();

    bool                     load(const std::string& path);
    bool                     has(ResourceId& id);
    Json*                    get(ResourceId& id);

private:
    std::map<std::string, std::unique_ptr<Json>> m_loaded;
};
