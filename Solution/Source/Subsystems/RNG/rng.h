#pragma once

#include <climits>
#include <random>

#include "json_aliases.h"

class RNG
{
public:
    RNG(int seed = 0, int min = INT_MIN, int max = INT_MAX);

    int get() const;
    int getFrom(int min, int max) const;

    void load(const Json& node);
    Json save() const;

private:
    int m_min;
    int m_max;

    mutable std::mt19937 m_engine;
    std::uniform_int_distribution<int> m_dist;
};
