#include "rng.h"

#include <cassert>
#include <cstdlib>

RNG::RNG(int seed, 
         int min, 
         int max) :
    m_min(min),
    m_max(max),
    m_engine(seed),
    m_dist(min, max)
{
    assert(min <= max && "RNG: min > max on construction");
}

int RNG::get() const
{
    return m_dist(m_engine);
}

int RNG::getFrom(int min, int max) const
{
    assert(min <= max && "RNG: min > max on get");
    int val = m_dist(m_engine);
    long long defRange = abs(long long(m_max) - m_min);
    long long newRange = abs(long long(max) - min + 1);
    double rescaled = double(abs(long long(val) - m_min)) / defRange * newRange;
    return min + floor(rescaled);
}

void RNG::load(Json& node)
{
    m_min = node.at("min").get<int>();
    m_max = node.at("max").get<int>();
    m_dist = std::uniform_int_distribution<int>(m_min, m_max);
    std::stringstream ss;
    ss << node.at("engine").get<std::string>();
    ss >> m_engine;
}

Json RNG::save() const
{
    Json result;
    result["min"] = m_min;
    result["max"] = m_max;
    std::stringstream ss;
    ss << m_engine;
    result["engine"] = ss.str();
    return result;
}
