#include "factory__widget.h"

#include "system__resource.h"
#include "parser__widget.h"

WidgetFactory::WidgetFactory() :
    m_parser(new WidgetParser())
{}

bool WidgetFactory::init(ResourceSystem& resSystem)
{
    auto inited = true;
    inited = inited && m_parser->init(resSystem);
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
