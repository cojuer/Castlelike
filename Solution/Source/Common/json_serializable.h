#pragma once

#include <string>

#include "json_aliases.h"

class ResourceSystem;

class JSONSerializable
{
public:
    virtual Json save() const = 0;
    virtual void load(const Json& node, ResourceSystem& resSystem) = 0;

    virtual std::string getStringID() const = 0;
};
