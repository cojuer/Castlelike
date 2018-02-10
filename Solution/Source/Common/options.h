#pragma once

#include <map>
#include <string>

namespace OptType
{
const std::string WIDTH = "Width";
const std::string HEIGHT = "Height";
}

/**
 * Storage for options loaded from ini file.
 */
class Options
{
public:
    bool loadFile(std::string path);

    template <typename T>
    T get(const std::string& key) const
    {
        auto iter = m_data.find(key);
        return iter != m_data.end() ? iter->second : T{};
    }

    std::string& operator[](std::string key);
    const std::string& at(std::string key) const;

private:
    static bool isBlockName(const std::string& line);
    static bool isLineValid(const std::string& line);

    void parse(std::ifstream& stream);

private:
    std::map<std::string, std::string> m_data;
};

template <>
uint32_t Options::get<uint32_t>(const std::string& key) const;

template <>
int32_t Options::get<int32_t>(const std::string& key) const;

template <>
bool Options::get<bool>(const std::string& key) const;