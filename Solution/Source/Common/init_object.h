#pragma once

#include "object.h"

class InitObject : public Object
{
public:
    InitObject() : m_initialized(false) {}

    InitObject(const InitObject& another) = default;
    InitObject(InitObject&& another) = default;
    InitObject& operator=(const InitObject& rhs) = default;
    InitObject& operator=(InitObject&& rhs) = default;

    virtual ~InitObject() = default;

    void setInitialized() { m_initialized = true; }

    bool isInitialized() const { return m_initialized; }

protected:
    bool m_initialized;
};