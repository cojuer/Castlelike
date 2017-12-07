#include "text_manager.h"

#include <iostream>
#include <loader_json.h>

TextManager::TextManager()
{
    m_loader.load(source);
}

TextManager& TextManager::instance()
{
    static auto instance = new TextManager();
    return *instance;
}

const std::string& TextManager::getCopy(std::string str)
{
    m_strings.insert(str);
    return *m_strings.find(str);
}

const std::string& TextManager::getPhrase(const std::string& id)
{
    if (m_phrases.find(id) == m_phrases.end())
    {
        if (m_loader.has(id))
        {
            auto phrase = m_loader.get(id)->get<std::string>();
            m_phrases.insert(std::pair<std::string, std::string>(id, phrase));
        }
        else
        {
            return getCopy(id);
        }
    }
    return m_phrases.at(id);
}

const std::string& TextManager::getName(const std::string& resName)
{
    return getPhrase(resName + "_name");
}

const std::string& TextManager::getDescription(const std::string& resName)
{
    return getPhrase(resName + "_desc");
}

void TextManager::clean(const std::string& resName)
{
    auto iter = m_phrases.find(resName + "_name");
    if (iter != m_phrases.end())
    {
        m_phrases.erase(iter);
    }
    iter = m_phrases.find(resName + "_desc");
    if (iter != m_phrases.end())
    {
        m_phrases.erase(iter);
    }
}
