#pragma once

#include <map>
#include <string>

#include "rng.h"

namespace RNGType
{
const std::string AREA = "area";
const std::string LOOT = "loot";
}

class RNGHolder
{
public:
    RNG* regRNG(const std::string& name, RNG rng);
    RNG* getRNG(const std::string& name);

    void load(Json& node);
    Json save() const;

private:
    std::map<std::string, RNG> m_rngs;
};