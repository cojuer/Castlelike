#include "factory__dialogue.h"

#include "loader__json.h"
#include "parser__dialogue.h"

#include <iostream>

DialFactory::DialFactory() :
    m_loader(new JsonLoader()),
    m_parser(new DialogueParser())
{}

bool DialFactory::load(const std::string& fname)
{
    bool flag = true;
    m_loader->load(fname);
    return flag;
}

Resource<Dialogue>* DialFactory::get(ResourceId& id)
{
    Dialogue* dial = nullptr;
    auto node = m_loader->get(id);
    if (node && !node->is_null())
    {
        dial = m_parser->parse(id, *node);
    }
    return dial;
}
