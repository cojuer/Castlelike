#include "rng_holder.h"

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

void RNGHolder::load(Json& node)
{
    for (auto it = node.begin(); it != node.end(); ++it) 
    {
        RNG rng;
        rng.load(it.value());
        m_rngs[it.key()] = rng;
    }
}

Json RNGHolder::save() const
{
    Json result;
    // TODO: use C++17 when intellisense support is available
    for (auto& pair : m_rngs)
    {
        auto& name = pair.first;
        auto& rng = pair.second;
        result[name] = rng.save();
    }
    return result;
}
