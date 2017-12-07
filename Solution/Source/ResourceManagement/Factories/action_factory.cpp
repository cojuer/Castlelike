#include "action_factory.h"

#include <iostream> // TEST

#include "resource_manager.h"
#include "actions.h"
#include "action__move.h"

ActFactory::ActFactory(ResourceManager& resManager) :
    m_mgr(resManager.actionManager)
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