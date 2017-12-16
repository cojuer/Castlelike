#include "factory__renderable.h"

#include "renderable_cache.h"
#include "renderable_loader.h"
#include "resource_manager.h"

RenderableFactory::RenderableFactory() :
    m_cache(new RenderableCache()),
    m_loader(new RenderableLoader())
{}

bool RenderableFactory::init(ResourceManager& resManager, RenderSubsystem& rendSubsystem)
{
    auto inited = true;
    inited = inited && m_loader->init(resManager, rendSubsystem);
    return inited;
}

bool RenderableFactory::load(const std::string& fname)
{
    auto loaded = true;
    loaded = loaded && m_loader->load(fname);
    return loaded;
}

Resource<Renderable>* RenderableFactory::get(ResourceId& id)
{
    if (m_cache->has(id))
    {
        return &m_cache->get(id);
    }
    else
    {
        auto resource = m_loader->get(id);
        if (resource)
        {
            m_cache->add(id, *resource);
        }
        return resource;
    }
}

Resource<Renderable>& RenderableFactory::get(ResourceId& id, SDL_Rect geometry)
{
	if (m_cache->has(id))
	{
		auto result = m_cache->get(id).clone();
		dynamic_cast<ATexture*>(result)->setSrcRect(geometry);
		dynamic_cast<ATexture*>(result)->setWidth(geometry.w);
		dynamic_cast<ATexture*>(result)->setHeight(geometry.h);
		return *result;
	}
	else
	{
		auto loadedResource = m_loader->get(id);
        if (loadedResource)
        {
            m_cache->add(id, *loadedResource);
            loadedResource = loadedResource->clone();
            dynamic_cast<ATexture*>(loadedResource)->setSrcRect(geometry);
            dynamic_cast<ATexture*>(loadedResource)->setWidth(geometry.w);
            dynamic_cast<ATexture*>(loadedResource)->setHeight(geometry.h);
        }
        // FIXME: can be nullptr
		return *loadedResource;
	}
}

RenderableFactory::~RenderableFactory()
{
    delete(m_cache);
    delete(m_loader);
}
