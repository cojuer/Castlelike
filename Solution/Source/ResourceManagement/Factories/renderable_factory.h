#pragma once

#include <SDL.h>

#include "factory.h"
#include "pugi_aliases.h"

class Renderable;
class RenderSubsystem;
class RenderableCache;
class RenderableLoader;
class ResourceManager;

class RenderableFactory : public Factory<Renderable>
{
public:
    RenderableFactory();

    bool init(ResourceManager& resManager, RenderSubsystem& rendSubsystem);

    bool      load(const std::string& fname) override;
    Resource<Renderable>* get(ResourceId& id) override;
	Resource<Renderable>& get(ResourceId& id, SDL_Rect geometry);

    ~RenderableFactory();

private:
    RenderableCache*   m_cache;
    RenderableLoader*  m_loader;
};

