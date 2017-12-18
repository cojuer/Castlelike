#pragma once

#include <memory>

#include "parser_json.h"

#include "tileset.h"

class ResourceManager;

class TilesetParser : JsonParser<Tileset*>
{
public:
    TilesetParser();

    bool init(ResourceManager& resManager);

    Tileset* parse(const std::string& nodeName, Json& node) override;

private:
    ResourceManager* m_resManager;
};
