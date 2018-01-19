#pragma once

#include "resource.h"
#include "resource_id.h"

template<class T>
class Cache
{
public:
    virtual void add(ResourceId& id, Resource<T>& resource) = 0;
    virtual bool has(ResourceId& id) = 0;
    virtual Resource<T>& get(ResourceId& id) = 0;

    virtual ~Cache() = default;
};

