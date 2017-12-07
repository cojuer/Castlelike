#pragma once

#include "json_aliases.h"

template<class T>
class JsonParser
{
public:
    virtual ~JsonParser() {};

    virtual T parse(const std::string& nodeName, Json& node) = 0;
};