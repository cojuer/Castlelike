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
    
    int                  m_level;
    int                  m_value;
    int                  m_maxAmount;
    
    bool                 m_consumable;

    Modifiers*           m_modifiers;
    Action*              m_action;
};