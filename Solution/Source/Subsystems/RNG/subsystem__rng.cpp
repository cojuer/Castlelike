#include "subsystem__rng.h"

const std::string RNGHolder::stringID = "subsystem__rng";

RNG* RNGHolder::regRNG(const std::string& name, RNG rng)
{
    auto it = m_rngs.insert({ name, rng });
    return &it.first->second;
}

RNG* RNGHolder::getRNG(const std::string& name)
{
    auto it = m_rngs.find(name);
    if (it != m_rngs.end())
    {
        return &(it->second);
    }
    return nullptr;
}

void RNGHolder::load(const Json& node, ResourceSystem& resSystem)
{
    for (auto it = node.begin(); it != node.end(); ++it) 
    {
        RNG rng;
        rng.load(Json{ it.value() });
        m_rngs[it.key()] = rng;
    }
}

Json RNGHolder::save() const
{
    Json result;
    for (auto& [name, rng] : m_rngs)
    {
        result[name] = rng.save();
    }
    return result;
}

std::string RNGHolder::getStringID() const
{
    return stringID;
}
