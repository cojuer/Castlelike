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

    // TODO: use template
    int getInt(std::string key) const;

    std::string& operator[](std::string key);
    const std::string& at(std::string key) const;

private:
    static bool isBlockName(const std::string& line);
    static bool isLineValid(const std::string& line);

    void parse(std::ifstream& stream);

private:
    std::map<std::string, std::string> m_data;
};