#pragma once

#include <SDL.h>

#include "factory.h"
#include "cache__renderable.h"
#include "loader__renderable.h"

class Renderable;
class RenderSubsystem;
class ResourceSystem;

class RenderableFactory : public Factory<Renderable>
{
public:
    RenderableFactory() = default;

    bool init(ResourceSystem& resSystem, RenderSubsystem& rendSubsystem);

    bool      load(const std::string& fname) override;
    Resource<Renderable>* get(ResourceId& id) override;
	Resource<Renderable>& get(ResourceId& id, SDL_Rect geometry);

private:
    RenderableCache   m_cache;
    RenderableLoader  m_loader;
};


