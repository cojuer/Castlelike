#pragma once

class Object 
{
public:
    Object() = default;

    Object(const Object& another) = default;
    Object(Object&& another) = default;
    Object& operator=(const Object& rhs) = default;
    Object& operator=(Object&& rhs) = default;

    virtual ~Object() = default;
};
