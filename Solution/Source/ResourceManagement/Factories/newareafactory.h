#pragma once

#include "pugi_aliases.h"
#include "factory.h"
#include "scene.h"

class ResourceManager;

class NewSceneFactory : public Factory<Scene>
{
public:
    NewSceneFactory() = default;

    bool      init(ResourceManager& resManager);

    bool      load(const std::string& fname) override;
    Resource<Scene>* get(ResourceId& id) override;

private:
    PugiDoc          m_parseResult;
    ResourceManager* m_resManager;

private:
    std::vector<int> split(const std::string &s, char delim) const;
};