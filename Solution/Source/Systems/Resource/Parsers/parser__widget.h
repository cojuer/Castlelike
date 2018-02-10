#pragma once

#include <queue>

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
    WidgetParser() = default;

    bool         init(ResourceSystem& resSystem, const Options& opts);

    gui::Widget* parse(const std::string& nodeName, Json& node) override;

protected:
    gui::Widget* parseWidg(std::string nodeName, 
                           Json& widgNode, 
                           gui::Widget* parent, 
                           ParseQueue& parseQueue);

private:
    const Options*  m_opts { nullptr };
    ResourceSystem* m_resSystem{ nullptr };

    ParseQueue      m_parseQueue;
};