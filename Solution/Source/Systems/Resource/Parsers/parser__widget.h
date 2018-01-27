#pragma once

#include <queue>
#include <vector>

#include "json_aliases.h"
#include "parser__json.h"

class Options;

namespace gui {
class Widget;
} /* gui namespace. */

class ResourceSystem;

class WidgetParser : public JsonParser<gui::Widget*>
{
    using ParseQueue = std::queue<std::tuple<std::string, Json, gui::Widget*>>;

public:
    WidgetParser();

    bool         init(ResourceSystem& resSystem, const Options& opts);

    gui::Widget* parse(const std::string& nodeName, Json& node) override;

protected:
    gui::Widget* parseWidg(std::string name, Json& widg, gui::Widget* parent, ParseQueue& parseQueue);

private:
    const Options*  m_opts;
    ParseQueue      m_parseQueue;
    ResourceSystem* m_resSystem;
};