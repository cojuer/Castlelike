#pragma once

#include <queue>
#include <vector>

#include "json_aliases.h"
#include "parser_json.h"

namespace gui {
class Widget;
} /* gui namespace. */

class ResourceManager;

class WidgetParser : public JsonParser<gui::Widget*>
{
    using ParseQueue = std::queue<std::tuple<std::string, Json, gui::Widget*>>;

public:
    WidgetParser();

    bool         init(ResourceManager& resManager);

    gui::Widget* parse(const std::string& nodeName, Json& node) override;

protected:
    gui::Widget* parseWidg(std::string name, Json& widg, gui::Widget* parent, ParseQueue& parseQueue);

private:
    ParseQueue       m_parseQueue;
    ResourceManager* m_resManager;
};