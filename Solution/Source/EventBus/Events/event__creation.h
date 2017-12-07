#pragma once

#include <string>

#include "event.h"

enum class CreationEvType
{
    INC,
    DEC,
    SET
};

class CreationEvent : public Event
{
public:
    const CreationEvType type;
    const std::string    attrType;
    const int            value;

    CreationEvent(CreationEvType type, const std::string& attrType, int value = 0, Object* sender = nullptr);
    virtual ~CreationEvent();
};
