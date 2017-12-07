#include "renderable_cache.h"

void RenderableCache::add(ResourceId& id, Resource<Renderable>& resource)
{
    m_data[id] = &resource;
}

bool RenderableCache::has(ResourceId& id)
{
    return m_data.find(id) != m_data.end();
}

Resource<Renderable>& RenderableCache::get(ResourceId& id)
{
    return *m_data.at(id);
}