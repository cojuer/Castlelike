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

int Options::getInt(std::string key) const
{
    return std::stoi(m_data.at(key));
}

std::string& Options::operator[](std::string key)
{
    return m_data[key];
}

const std::string& Options::at(std::string key) const
{
    return m_data.at(key);
}
