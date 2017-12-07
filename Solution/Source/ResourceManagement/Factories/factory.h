#pragma once

#include "resource.h"
#include "resource_id.h"

template<class T>
class Factory
{
public:
    Factory() = default;

    Factory(const Factory& another) = delete;
    Factory(Factory&& another) = delete;
    Factory& operator=(const Factory& other) = delete;
    Factory& operator=(Factory&& other) = delete;

    virtual bool         load(const std::string& fname) = 0;
    virtual Resource<T>* get(ResourceId& name) = 0;

    virtual ~Factory() = default;

    using type = T;
};