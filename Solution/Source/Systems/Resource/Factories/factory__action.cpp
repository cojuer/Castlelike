#include "factory__action.h"

#include <iostream> // TEST

#include "system__resource.h"
#include "actions.h"
#include "action__move.h"

ActFactory::ActFactory(ResourceSystem& resSystem) :
    m_mgr(resSystem.actionManager)
{}

// TODO: rewrite
ActionInterface& ActFactory::parse(PugiNode& node)
{
    // FIXME: rework for json
    return *new MoveAction();
}

bool ActFactory::load(const std::string& fname)
{
    auto result = m_parseResult.load_file(fname.c_str());

    if (result)
    {
        std::cout << "Action data loaded" << std::endl;
        return true;
    }
    return false;
}

Resource<ActionInterface>* ActFactory::get(ResourceId& id)
{
    // FIXME
    return new MoveAction{};
}