#pragma once

#include <map>

#include "cache.h"

class Renderable;

class RenderableCache : public Cache<Renderable>
{
public:
    void add(ResourceId& id, Resource<Renderable>& resource) override;
    bool has(ResourceId& id) override;
    Resource<Renderable>& get(ResourceId& id) override;

private:
    std::map<ResourceId, Resource<Renderable>*> m_data;
};