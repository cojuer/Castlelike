#pragma once

#include "object.h"

class InitObject : public Object
{
public:
    InitObject() : m_initialized(false) {}
    virtual ~InitObject() = default;

    InitObject(const InitObject& another) = default;
    InitObject(InitObject&& another) = default;

    void setInitialized() { m_initialized = true; }

    bool isInitialized() const { return m_initialized; }

protected:
    bool m_initialized;
};