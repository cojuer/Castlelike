#include "factory__widget.h"

#include "resource_manager.h"
#include "parser_widget.h"

WidgetFactory::WidgetFactory() :
    m_parser(new WidgetParser())
{}

bool WidgetFactory::init(ResourceManager& resManager)
{
    auto inited = true;
    inited = inited && m_parser->init(resManager);
    return inited;
}

bool WidgetFactory::load(const std::string& fname)
{
    auto loaded = true;
    loaded = loaded && m_loader.load(fname);
    return loaded;
}

Resource<gui::Widget>* WidgetFactory::get(ResourceId& id)
{
    auto node = m_loader.get(id);
    if (node)
    {
        return m_parser->parse(id, *node);
    }
    return nullptr;
}

WidgetFactory::~WidgetFactory()
{
    delete(m_parser);
}
