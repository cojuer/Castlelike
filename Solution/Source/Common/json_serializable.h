#pragma once

#include <string>

#include "json_aliases.h"

class ResourceSystem;

class JSONSerializable
{
public:
    JSONSerializable() = default;

    JSONSerializable(const JSONSerializable& another) = default;
    JSONSerializable(JSONSerializable&& another) = default;
    JSONSerializable& operator=(const JSONSerializable& rhs) = default;
    JSONSerializable& operator=(JSONSerializable&& rhs) = default;

    virtual ~JSONSerializable() = default;

    virtual Json save() const = 0;
    virtual void load(const Json& node, ResourceSystem& resSystem) = 0;

    virtual std::string getStringID() const = 0;
};
