#pragma once

#include "actor.h"
#include "factory.h"
#include "loader__json.h"

class ActorFactory : public Factory<Actor>
{
public:
    ActorFactory() = default;

    bool init(ResourceSystem& resSystem);

    bool load(const std::string& fname) override;
    Resource<Actor>* get(ResourceId& name) override;
    Resource<Actor>* generateActor(Json& node);
    Resource<Actor>* loadActor(Json& node);

private:
    template<typename T>
    void regToAddCompMap(std::string strCompId);

    void generateComps(const Json& node, Actor& actor);
    void postGenerateComps(Actor& actor);

    void loadComps(const Json& node, Actor& actor);
    void postLoadComps(Actor& actor);

private:
    ResourceSystem* m_resSystem { nullptr };
    JsonLoader      m_loader;

    std::map<std::string, void(Actor::*)(ActorComponent&)> addComp;
};
