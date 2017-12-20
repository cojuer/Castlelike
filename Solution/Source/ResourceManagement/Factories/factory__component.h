#pragma once

#include "component.h"
#include "factory.h"
#include "loader__json.h"

class ComponentFactory : public Factory<ActorComponent>
{
public:
    ComponentFactory();

    bool init(ResourceManager& resManager);
    bool load(const std::string& fname) override;

    Resource<ActorComponent>* get(ResourceId& id) override;
    Resource<ActorComponent>* createCompFromJSON(const std::string& type, Json& node);

private:
    ResourceManager* m_resManager;
    JsonLoader m_loader;
    std::map<std::string, ActorComponent*(*)()> m_map;
};
