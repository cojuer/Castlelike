#include "item_prototype.h"

ItemProto::ItemProto() :
    m_class(""),
    m_type(""),
    m_resID(""),
    m_viewID(""),
    m_level(0),
    m_value(0),
    m_maxAmount(1),
    m_consumable(false),
    m_modifiers(nullptr),
    m_action(nullptr)
{}