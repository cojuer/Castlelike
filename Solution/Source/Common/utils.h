#pragma once

#include <vector>
#include <string>

#include "vec2.h"

#define dcast dynamic_cast

namespace utils
{
    void logassert(bool expression, const std::string& info);

    int coordDist(Vec2i a, Vec2i b);
    int euclDist(Vec2i a, Vec2i b);

    std::string format(std::string& str, std::vector<std::string>& args);
}