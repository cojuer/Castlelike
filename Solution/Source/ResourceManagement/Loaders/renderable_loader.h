#pragma once

#include "atexture.h"
#include "loader.h"
#include "pugi_aliases.h"

class Renderable;
class ResourceManager;

class RenderableLoader : public Loader<Renderable*>
{
public:
    RenderableLoader();

    bool             init(ResourceManager& resManager, RenderSubsystem& rendSubsystem);

    bool             load(const std::string& fname) override;
    bool             has(ResourceId& id) override;
    Renderable*      get(ResourceId& id) override;

protected:
    Renderable*      getTexture(PugiNode& node) const;
    Renderable*      getAnimation(PugiNode& node) const;
    Renderable*      getSprSheet(PugiNode& node) const;

private:
    ResourceManager* m_resManager;
    RenderSubsystem* m_rendSubsystem;
    PugiDoc          m_parseResult;
};