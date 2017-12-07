#include "journal.h"

#include <string>

#include "event_bus.h"
#include "listener__text.h"
#include "utils.h"
#include "text_manager.h"

Journal::Journal()
{
    auto listener = new TextListener(*this);
    EventBus::AddHandler(*listener);
}

void Journal::addEntry(std::string type, EntryArgs args)
{
    auto& mgr = TextManager::instance();
    auto str = mgr.getPhrase(type);
    EntryArgs langArgs;
    for (auto arg : args)
    {
        langArgs.push_back(mgr.getPhrase(arg));
    }
    auto res = utils::format(str, langArgs);
    entries.push_back(res);
}

size_t Journal::getSize() const
{
    return entries.size();
}

const std::string& Journal::getEntry(unsigned int number) const
{
    return entries[number];
}