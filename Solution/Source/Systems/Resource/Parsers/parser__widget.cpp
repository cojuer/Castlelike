#include "parser__widget.h"

#include "system__resource.h"

#include "widget.h"
#include "widget__button.h"
#include "widget__progress_bar.h"
#include "gui_elem__bag_widget.h"
#include "gui_elem__equip_widget.h"
#include "gui_elem__action_panel.h"
#include "gui_elem__loading.h"

bool WidgetParser::init(ResourceSystem& resSystem, const Options& opts)
{
    m_opts = &opts;
    m_resSystem = &resSystem;
    return true;
}

gui::Widget* WidgetParser::parseWidg(std::string nodeName, Json& widgNode, gui::Widget* parent, ParseQueue& parseQueue)
{
    gui::Widget* widg = nullptr;

    std::string type = widgNode["type"];

    // TODO: use some map
    if (type == "actpanel")      widg = new gui::ActPanel();
    else if (type == "button")   widg = new gui::Button();
    else if (type == "progbar")  widg = new gui::ProgressBar();
    else if (type == "bag")      widg = new gui::BagWidget();
    else if (type == "equip")    widg = new gui::EquipmentWidget();
    else if (type == "load_wdg") widg = new gui::LoadingWidget();
    else if (widg == nullptr)    widg = new gui::Widget(nullptr);

    widg->setVisible(true);
    widg->setName(nodeName);
    widg->setParent(parent);
    widg->load(widgNode, *m_resSystem, *m_opts);

    auto& children = widgNode["children"];
    for (auto it = children.begin(); it != children.end(); ++it)
    {
        parseQueue.push({ it.key(), it.value(), widg });
    }

    return widg;
}

gui::Widget* WidgetParser::parse(const std::string& nodeName, Json& node)
{
    auto widg = parseWidg(nodeName, node, nullptr, m_parseQueue);
    while (!m_parseQueue.empty())
    {

        auto child = parseWidg(std::get<0>(m_parseQueue.front()),
                               std::get<1>(m_parseQueue.front()),
                               std::get<2>(m_parseQueue.front()),
                               m_parseQueue);
        std::get<2>(m_parseQueue.front())->addChild(*child);
        m_parseQueue.pop();
    }
    widg->setVisible(true);
    return widg;
}
