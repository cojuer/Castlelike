#include "modifiers.h"

#include <string>

#include "utils.h"

const std::vector<std::string> Modifiers::dmgTypes = {
    "dmg_ph",  "dmg_mgc",
    "dmg_ch",  "dmg_fr",
    "dmg_frz", "dmg_psn",
    "dmg_lig",
};

const std::vector<std::string> Modifiers::armTypes = {
    "arm_ph",  "arm_mgc"
};

const std::vector<std::string> Modifiers::types = {
    "dmg_ph",  "dmg_mgc",
    "dmg_ch",  "dmg_fr",
    "dmg_frz", "dmg_psn",
    "dmg_lig",
    "res_ph",  "res_mgc",
    "res_ch",  "res_fr",
    "res_frz", "res_psn",
    "res_lig",
    "arm_ph",  "arm_mgc",
    "dodge",   "accuracy",
    "def_rating",
    "off_rating"
};

/* Save references to modifiers after copy construction. */
Modifiers::Modifiers(const Modifiers& another)
{
    for (auto& pair : m_data)
    {
        pair.second = 0;
    }
    for (auto& pair : another.m_data)
    {
        m_data[pair.first] = pair.second;
    }
}

int& Modifiers::operator[](const std::string& name)
{
    const auto iter = std::find(types.begin(), types.end(), name);
    utils::logassert(iter != types.end(), std::string("wrong modifier type: ") + name);
    return m_data[name];
}

int& Modifiers::operator[](const std::string&& name)
{
    const auto iter = std::find(types.begin(), types.end(), name);
    utils::logassert(iter != types.end(), std::string("wrong modifier type: ") + name);
    return m_data[name];
}

const int& Modifiers::at(const std::string& name) const
{
    const auto iter = std::find(types.begin(), types.end(), name);
    utils::logassert(iter != types.end(), std::string("wrong modifier type: ") + name);
    return m_data.at(name);
}

int Modifiers::weak_at(const std::string& name) const
{
    const auto iter = std::find(types.begin(), types.end(), name);
    utils::logassert(iter != types.end(), std::string("wrong modifier type: ") + name);
    return (m_data.find(name) != m_data.end()) ? m_data.at(name) : 0;
}

const std::map<std::string, int>& Modifiers::data() const
{
    return m_data;
}

Modifiers& Modifiers::operator=(const Modifiers& another)
{
    for (auto& pair : m_data)
    {
        pair.second = 0;
    }
    for (auto& pair : another.m_data)
    {
        m_data[pair.first] = pair.second;
    }
    return *this;
}

const std::string& Mdfr(const std::string& str)
{
    utils::logassert(std::count(Modifiers::types.begin(), Modifiers::types.end(), str), 
                     "wrong modifier name");
    return str;
}

const std::string& Dmg(const std::string& str)
{
    utils::logassert(std::count(Modifiers::dmgTypes.begin(), Modifiers::dmgTypes.end(), str),
                     "wrong damage name");
    return str;
}

// FIXME: use resistance types
const std::string& Rsst(const std::string& str)
{
    utils::logassert(std::count(Modifiers::types.begin(), Modifiers::types.end(), str),
                     "wrong resistance name");
    return str;
}

// FIXME: use armor types
const std::string& Arm(const std::string& str)
{
    utils::logassert(std::count(Modifiers::types.begin(), Modifiers::types.end(), str),
                     "wrong modifier name");
    return str;
}

Modifiers::operator std::string() const
{
    std::string result;
    for (auto& mdfr : m_data)
    {
        result += mdfr.first + " " + std::to_string(mdfr.second) + "\n";
    }
    return result;
}