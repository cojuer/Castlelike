#pragma once

#pragma once

#include "action_manager.h"
#include "factory.h"
#include "pugi_aliases.h"

class ResourceSystem;

class ActFactory : public Factory<ActionInterface>
{
public:
    explicit ActFactory(ResourceSystem& resSystem);

    static ActionInterface&    parse(PugiNode& node);

    bool              load(const std::string& fname) override;
    Resource<ActionInterface>* get(ResourceId& id) override;

private:
    ActMgr*     m_mgr;
    PugiDoc     m_parseResult;
};