#pragma once

#include <map>
#include <set>

#include "loader_json.h"

class TextManager
{
    static constexpr auto source = "Assets\\Databases\\textDB.json";

public:
    static TextManager& instance();

    const std::string& getCopy(std::string);
    const std::string& getPhrase(const std::string& id);
    const std::string& getName(const std::string& resName);
    const std::string& getDescription(const std::string& resName);

    void               clean(const std::string& resName);

private:
    JsonLoader            m_loader;
    std::set<std::string> m_strings;
    std::map<std::string, const std::string> m_phrases;

    TextManager();
};
