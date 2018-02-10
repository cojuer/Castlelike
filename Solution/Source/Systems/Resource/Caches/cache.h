#pragma once

#include "resource.h"
#include "resource_id.h"

template<class T>
class Cache
{
public:
    Cache() = default;

    Cache(const Cache&) = delete;
    Cache(Cache&&) = delete;
    Cache& operator=(const Cache&) = delete;
    Cache& operator=(Cache&&) = delete;

    virtual ~Cache() = default;

    virtual void add(ResourceId& id, Resource<T>& resource) = 0;
    virtual bool has(ResourceId& id) = 0;
    virtual Resource<T>& get(ResourceId& id) = 0;
};

