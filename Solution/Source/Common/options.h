#pragma once

#include <map>
#include <string>

/**
 * Storage for options loaded from ini file.
 */
class Options
{
public:
    bool loadFile(std::string path);

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