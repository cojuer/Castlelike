#pragma once

#include "event.h"

class TextListener;

class TextEvent : public Event
{
    friend class TextListener;
private:
    std::string type;
    std::vector<std::string> args;
public:
    TextEvent(std::string type,
              std::vector<std::string> args,
              Object* sender = nullptr) :
            Event(sender),
            type(type),
            args(args)
    {}

    virtual ~TextEvent() {};
};