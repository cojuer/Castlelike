#pragma once

#include "component.h"
#include "factory.h"
#include "loader__json.h"

class ComponentFactory : public Factory<ActorComponent>
{
public:
    ComponentFactory();

    bool init(ResourceSystem& resSystem);
    bool load(const std::string& fname) override;

    Resource<ActorComponent>* get(ResourceId& id) override;
    Resource<ActorComponent>* loadComp(const std::string& type, Json& node);
    Resource<ActorComponent>* generateComp(const std::string& type, Json& node);

private:
    ResourceSystem* m_resSystem;
    JsonLoader m_loader;
    std::map<std::string, ActorComponent*(*)()> m_map;
};
