#pragma once

#include "component.h"
#include "factory.h"
#include "loader_json.h"

class ComponentFactory : public Factory<ActorComponent>
{
public:
    ComponentFactory();

    bool init(ResourceManager& resManager);
    bool load(const std::string& fname) override;
    Resource<ActorComponent>* get(ResourceId& id) override;

private:
    ResourceManager* m_resManager;
    JsonLoader m_loader;
    std::map<std::string, ActorComponent*(*)()> m_map;
};
