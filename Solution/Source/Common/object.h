#pragma once

class Object 
{
public:
    Object() = default;
    virtual ~Object() = default;

    Object(const Object& another) = default;
    Object(Object&& another) = default;
};
