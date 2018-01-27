#pragma once

#include "factory.h"
#include "pugi_aliases.h"
#include "loader__json.h"
#include "parser__widget.h"

class Options;

namespace gui {
class Widget;
} /* gui namespace */

class ResourceSystem;

class WidgetFactory : public Factory<gui::Widget>
{
public:
    WidgetFactory();

    bool init(ResourceSystem& resSystem, const Options& opts);

    bool                  load(const std::string& fname) override;
    Resource<gui::Widget>* get(ResourceId& id) override;

    ~WidgetFactory();

private:
    const Options* m_opts;
    JsonLoader     m_loader;
    WidgetParser   m_parser;
    PugiDoc        m_parseResult;
};