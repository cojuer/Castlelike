#pragma once

#include "resource_id.h"

template<class T>
class Loader
{
public:
    Loader() = default;

    Loader(const Loader&) = delete;
    Loader(Loader&&) = delete;
    Loader& operator=(const Loader&) = delete;
    Loader& operator=(Loader&&) = delete;

    virtual ~Loader() = default;

    virtual bool load(const std::string& fname) = 0;
    virtual bool has(ResourceId& id) = 0;
    virtual T get(ResourceId& id) = 0;
};


