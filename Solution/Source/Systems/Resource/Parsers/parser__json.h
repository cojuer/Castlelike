#pragma once

#include "json_aliases.h"

template<class T>
class JsonParser
{
public:
    JsonParser() = default;

    JsonParser(const JsonParser&) = delete;
    JsonParser(JsonParser&&) = delete;
    JsonParser& operator=(const JsonParser&) = delete;
    JsonParser& operator=(JsonParser&&) = delete;

    virtual ~JsonParser() = default;

    virtual T parse(const std::string& nodeName, Json& node) = 0;
};