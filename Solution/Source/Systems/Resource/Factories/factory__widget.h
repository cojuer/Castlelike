#pragma once

#include "factory.h"
#include "pugi_aliases.h"
#include "loader__json.h"

namespace gui {
class Widget;
} /* gui namespace */

class ResourceSystem;
class WidgetParser;

class WidgetFactory : public Factory<gui::Widget>
{
public:
    WidgetFactory();

    bool init(ResourceSystem& resSystem);

    bool                  load(const std::string& fname) override;
    Resource<gui::Widget>* get(ResourceId& id) override;

    ~WidgetFactory();

private:
    JsonLoader     m_loader;
    WidgetParser*  m_parser;
    PugiDoc        m_parseResult;
};