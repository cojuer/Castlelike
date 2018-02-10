#include "options.h"

#include <fstream>

bool Options::isBlockName(const std::string& line)
{
    return (line[0] == '[');
}

bool Options::isLineValid(const std::string& line)
{
    return (line.find('=') != std::string::npos);
}

bool Options::loadFile(std::string path)
{
    m_data.clear();

    std::ifstream stream(path);
    if (!stream.is_open())
    {
        return false;
    }
    
    parse(stream);

    return true;
}

template <>
uint32_t Options::get<uint32_t>(const std::string& key) const
{
    auto iter = m_data.find(key);
    return iter != m_data.end() ? std::stoul(iter->second) : 0;
}

template <>
int32_t Options::get<int32_t>(const std::string& key) const
{
    auto iter = m_data.find(key);
    return iter != m_data.end() ? std::stoi(iter->second) : 0;
}

template <>
bool Options::get<bool>(const std::string& key) const
{
    auto iter = m_data.find(key);
    return iter != m_data.end() ? std::stoi(iter->second) : false;
}

void Options::parse(std::ifstream& stream)
{
    std::string line;
    while (std::getline(stream, line))
    {
        if (!isLineValid(line)) continue;
        if (isBlockName(line))  continue;

        auto separator = line.find('=');
        auto key = line.substr(0, separator);
        auto value = line.substr(separator + 1);
        m_data[key] = value;
    }
}

std::string& Options::operator[](std::string key)
{
    return m_data[key];
}

const std::string& Options::at(std::string key) const
{
    return m_data.at(key);
}
