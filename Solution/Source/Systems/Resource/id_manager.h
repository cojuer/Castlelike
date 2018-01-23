#pragma once

#include <list>

#include "json_serializable.h"
#include "actor.h"

class ResourceSystem;

class IDManager : public JSONSerializable
{
public:
    IDManager();

    ActorID getActorID();
    void    free(ActorID id);

    void    load(const Json& node, ResourceSystem& resSystem) override;
    Json    save() const override;

    static IDManager& instance();

    std::string getStringID() const override;
    static const std::string stringID;

private:
    ActorID            m_current;
    std::list<ActorID> m_freed;
};