#pragma once

#include <memory>

#include "parser__json.h"

class ItemProto;

class IProtoParser : JsonParser<std::shared_ptr<const ItemProto>>
{
    using ItemProtoSPtr = std::shared_ptr<const ItemProto>;

public:
    IProtoParser() = default;

    ItemProtoSPtr parse(const std::string& nodeName, Json& node) override;
};