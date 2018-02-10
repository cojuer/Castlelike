#include "system__journal.h"

#include <string>

#include "subsystem__event.h"
#include "utils.h"
#include "text_manager.h"

JournalSystem::JournalSystem()
{
    m_reg.reset(EventSubsystem::AddHandler(*this));
}

JournalSystem::~JournalSystem()
{
    m_reg->removeHandler();
}

void JournalSystem::clean()
{
    m_entries.clear();
}

void JournalSystem::addEntry(std::string type, EntryArgs args)
{
    auto& mgr = TextManager::instance();
    auto str = mgr.getPhrase(type);
    EntryArgs langArgs;
    for (const auto& arg : args)
    {
        langArgs.push_back(mgr.getPhrase(arg));
    }
    auto res = utils::format(str, langArgs);
    m_entries.push_back(res);
}

size_t JournalSystem::getSize() const
{
    return m_entries.size();
}

const std::string& JournalSystem::getEntry(unsigned int number) const
{
    return m_entries[number];
}

void JournalSystem::onEvent(JournalEvent& event)
{
    std::cout << "on journal event" << std::endl;
    addEntry(event.type, event.args);
}