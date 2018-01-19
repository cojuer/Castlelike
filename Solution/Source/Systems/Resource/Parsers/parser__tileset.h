#pragma once

#include <memory>

#include "parser__json.h"

#include "tileset.h"

class ResourceSystem;

class TilesetParser : JsonParser<Tileset*>
{
public:
    TilesetParser();

    bool init(ResourceSystem& resSystem);

    Tileset* parse(const std::string& nodeName, Json& node) override;

private:
    ResourceSystem* m_resSystem;
};
