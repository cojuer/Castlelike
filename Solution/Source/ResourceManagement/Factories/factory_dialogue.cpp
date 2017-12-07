#include "factory_dialogue.h"

#include "loader_json.h"
#include "parser_dialogue.h"

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

DialFactory::~DialFactory() = default;
