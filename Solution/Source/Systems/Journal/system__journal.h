#pragma once

#include <memory>
#include <string>
#include <vector>

#include "handler_registration.h"
#include "event__journal.h"
#include "event_handler.h"

/**
* Journal system is used to create and store string entries,
* telling about different in-game events.
*/
class JournalSystem final : public EventHandler<JournalEvent>
{
public:
    using Entries = std::vector<std::string>;
    using EntryArgs = std::vector<std::string>;

public:
    JournalSystem();

    JournalSystem(const JournalSystem&) = delete;
    JournalSystem(JournalSystem&&) = delete;
    JournalSystem& operator=(const JournalSystem&) = delete;
    JournalSystem& operator=(JournalSystem&&) = delete;

    ~JournalSystem();

    void                 clean();

    void                 addEntry(std::string type, EntryArgs args);

    size_t               getSize() const;
    const std::string&   getEntry(unsigned int number) const;

    void onEvent(JournalEvent& event) override;

private:
    Entries m_entries;

    std::unique_ptr<HandlerRegistration> m_reg;
};