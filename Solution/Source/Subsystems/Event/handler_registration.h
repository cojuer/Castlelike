#pragma once

#include "object.h"

class HandlerRegistration : public Object
{
public:
    HandlerRegistration() = default;

    HandlerRegistration(const HandlerRegistration&) = default;
    HandlerRegistration(HandlerRegistration&&) = default;
    HandlerRegistration& operator=(const HandlerRegistration&) = default;
    HandlerRegistration& operator=(HandlerRegistration&&) = default;

    virtual ~HandlerRegistration() = default;

    virtual void removeHandler() = 0;
};
