#include "parser__item_proto.h"

#include "text_manager.h"

#include "item_prototype.h"

IProtoParser::ItemProtoSPtr IProtoParser::parse(const std::string& nodeName, Json& node)
{
    auto proto = new ItemProto();

    proto->m_resID = nodeName;

    proto->m_value = node["value"];

    proto->m_class = node["class"].get<std::string>();
    proto->m_type = node["type"].get<std::string>();

    proto->m_modifiers = new Modifiers();
    for (auto it = node["modifiers"].begin(); it != node["modifiers"].end(); ++it)
    {
        (*proto->m_modifiers)[Mdfr(it.key())] = it.value();
    }

    if (!node["max_amount"].is_null())
    {
        proto->m_maxAmount = node["max_amount"];
    }

    return std::shared_ptr<const ItemProto>(proto);
}
