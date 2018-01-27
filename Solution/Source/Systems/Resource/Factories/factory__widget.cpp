#include "factory__widget.h"

#include "system__resource.h"
#include "parser__widget.h"

WidgetFactory::WidgetFactory() :
    m_opts(nullptr)
{}

bool WidgetFactory::init(ResourceSystem& resSystem, const Options& opts)
{
    m_opts = &opts;

    auto inited = true;
    inited = inited && m_parser.init(resSystem, opts);
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
        return m_parser.parse(id, *node);
    }
    return nullptr;
}

WidgetFactory::~WidgetFactory() = default;
