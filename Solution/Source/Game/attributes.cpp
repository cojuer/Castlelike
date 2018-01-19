#include "attributes.h"

#include "utils.h"

const std::vector<std::string> Attributes::types = {
    "str",
    "int",
    "dex",
    "vit",
    "chr",
    "per"
};

int& Attributes::operator[](const std::string& name)
{
    const auto iter = std::find(types.begin(), types.end(), name);
    utils::logassert(iter != types.end(), std::string("wrong attribute type: ") + name);
    return m_data[name];
}

int& Attributes::operator[](const std::string&& name)
{
    const auto iter = std::find(types.begin(), types.end(), name);
    utils::logassert(iter != types.end(), std::string("wrong attribute type: ") + name);
    return m_data[name];
}

const int& Attributes::at(const std::string& name) const
{
    const auto iter = std::find(types.begin(), types.end(), name);
    utils::logassert(iter != types.end(), std::string("wrong attribute type: ") + name);
    return m_data.at(name);
}

int Attributes::weak_at(const std::string& name) const
{
    const auto iter = std::find(types.begin(), types.end(), name);
    utils::logassert(iter != types.end(), std::string("wrong attribute type: ") + name);
    return (m_data.find(name) != m_data.end()) ? m_data.at(name) : 0;
}

const std::map<std::string, int>& Attributes::data() const
{
    return m_data;
}

const std::string& Attr(const std::string& str)
{
    utils::logassert(std::count(Attributes::types.begin(), Attributes::types.end(), str),
                     "wrong attribute name");
    return str;
}
