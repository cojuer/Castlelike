#pragma once

#include "object.h"

class HandlerRegistration : public Object
{
public:
    virtual ~HandlerRegistration() {}
    virtual void removeHandler() = 0;
};
