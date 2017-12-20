#pragma once

#include "actor.h"
#include "factory.h"
#include "loader__json.h"

class ActorFactory : public Factory<Actor>
{
public:
    ActorFactory() = default;

    bool init(ResourceManager& resManager);

    bool load(const std::string& fname) override;
    Resource<Actor>* get(ResourceId& name) override;
    Resource<Actor>* createActorFromJSON(Json& node);

    ~ActorFactory();

private:
    template<typename T>
    void regToAddCompMap(std::string strCompId);

private:
    ResourceManager* m_resManager;
    JsonLoader       m_loader;

    std::map<std::string, void(Actor::*)(ActorComponent&)> addComp;
};
