#pragma once

#include <map>
#include <string>

#include "json_serializable.h"
#include "rng.h"

class ResourceSystem;

namespace RNGType
{
const std::string AREA = "area";
const std::string LOOT = "loot";
}

class RNGHolder : public JSONSerializable
{
public:
    RNG* regRNG(const std::string& name, RNG rng);
    RNG* getRNG(const std::string& name);

    void load(const Json& node, ResourceSystem& resSystem) override;
    Json save() const override;

    std::string getStringID() const override;
    static const std::string stringID;
private:
    std::map<std::string, RNG> m_rngs;
};