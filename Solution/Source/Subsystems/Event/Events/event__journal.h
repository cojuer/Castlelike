#pragma once

#include <string>
#include <vector>

#include "event.h"

class JournalEvent final : public Event
{
    friend class JournalSystem;
public:
    JournalEvent(std::string type,
                 std::vector<std::string> args,
                 Object* sender = nullptr) :
        Event(sender),
        type(std::move(type)),
        args(std::move(args))
    {}
   
private:
    std::string type;
    std::vector<std::string> args;

};