#pragma once

#include "modifiers.h"

struct Action;

class ItemProto
{
    friend class Item;
    friend class IProtoParser;

public:
    ItemProto();

private:
    std::string          m_class;
    std::string          m_type;

    std::string          m_resID;
    std::string          m_viewID;
    
    uint32_t             m_level;
    uint32_t             m_value;
    uint32_t             m_maxAmount;
    
    bool                 m_consumable;

    Modifiers*           m_modifiers;
    Action*              m_action;
};