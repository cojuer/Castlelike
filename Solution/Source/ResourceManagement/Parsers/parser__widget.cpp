#include "parser__widget.h"

#include <iostream>

#include "widget__button.h"
#include "widget__progress_bar.h"
#include "resource_manager.h"
#include "widget.h"
#include "bagwidget.h"
#include "equipmentwidget.h"
#include "game_gui.h"
#include "actpanel.h"

WidgetParser::WidgetParser() :
    m_resManager(nullptr)
{}

bool WidgetParser::init(ResourceManager& resManager)
{
    m_resManager = &resManager;
    return true;
}

gui::Widget* WidgetParser::parseWidg(std::string nodeName, Json& widgNode, gui::Widget* parent, ParseQueue& parseQueue)
{
    gui::Widget* widg = nullptr;

    std::string type = widgNode["type"];

    if (type == "actpanel") widg = new gui::ActPanel();
    else if (type == "button")   widg = new gui::Button();
    else if (type == "progbar")  widg = new gui::ProgressBar();
    else if (type == "bag")      widg = new gui::BagWidget();
    else if (type == "equip")    widg = new gui::EquipmentWidget();
    else if (widg == nullptr)    widg = new gui::Widget(nullptr);

    widg->setVisible(true);
    widg->setName(nodeName);
    widg->init(widgNode, *m_resManager);

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
