#pragma once

#include <map>
#include <vector>

// Debug functions
const std::string& Attr(const std::string& str);

class Attributes
{
public:
    const static std::vector<std::string> types;

    int& operator[](const std::string& name);
    int& operator[](const std::string&& name);
    const int& at(const std::string& name) const;
    int weak_at(const std::string& name) const;
    const std::map<std::string, int>& data() const;

private:
    std::map<std::string, int> m_data;
};