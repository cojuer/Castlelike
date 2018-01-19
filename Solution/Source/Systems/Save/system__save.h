#pragma once

#include <string>
#include <map>
#include <vector>

struct Character
{
    std::string name;
    // date
};

struct Save
{
    std::string name;
    // date
    // play time
};

class SaveSystem
{
    static const std::string extension;
    static const std::string format;

public:
    bool init();

    std::vector<Character> getCharacters() const;
    std::vector<Save> getSaves(const Character& character) const;

private:
    Character m_currCharacter;
    std::map<Character, std::vector<Save>> m_saves;
};