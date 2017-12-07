#pragma once

#include <map>
#include <vector>

// Debug functions
const std::string& Mdfr(const std::string& str);
const std::string& Dmg(const std::string& str);
const std::string& Rsst(const std::string& str);
const std::string& Arm(const std::string& str);

class Modifiers
{
public:
    const static std::vector<std::string> types;
    const static std::vector<std::string> dmgTypes;
    const static std::vector<std::string> armTypes;
    
    Modifiers() = default;
    Modifiers(const Modifiers& another);

    int& operator[](const std::string& name);
    int& operator[](const std::string&& name);
    const int& at(const std::string& name) const;
    int weak_at(const std::string& name) const;
    const std::map<std::string, int>& data() const;

    Modifiers& operator=(const Modifiers& another);
    explicit operator std::string() const;

private:
    std::map<std::string, int> m_data;
};