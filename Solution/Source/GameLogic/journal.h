#pragma once

#include <vector>

/**
 * Journal class is used to create and store string entries,
 * telling about different in-game events.
 */
class Journal
{
    using Entries   = std::vector<std::string>;
    using EntryArgs = std::vector<std::string>;

public:
    Journal();

    void                 addEntry(std::string res, EntryArgs args);

    size_t               getSize() const;
    const std::string&   getEntry(unsigned int number) const;

private:
    Entries entries;
};