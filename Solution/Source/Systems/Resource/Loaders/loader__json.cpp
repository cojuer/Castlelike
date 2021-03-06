#include "loader__json.h"

#include "subsystem_io.h"

bool JsonLoader::load(const std::string& path)
{
    m_loaded[path] = IOSubsystem::getJSON(path);
    return true;
}

bool JsonLoader::has(ResourceId& id)
{
    auto jsonPtr = (id[0] == '/' ? id : std::string("/") + id);
    for (auto&[path, rootNode] : m_loaded)
    {
        auto& node = (*rootNode)[JsonPointer(jsonPtr)];
        if (!node.is_null()) return true;
    }
    return false;
}

Json* JsonLoader::get(ResourceId& id)
{
    auto jsonPtr = (id[0] == '/' ? id : std::string("/") + id);
    for (auto&[path, rootNode] : m_loaded)
    {
        auto& node = (*rootNode)[JsonPointer(jsonPtr)];
        if (!node.is_null()) return &node;
    }
    return nullptr;
}