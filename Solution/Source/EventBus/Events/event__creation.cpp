#include "event__creation.h"

CreationEvent::CreationEvent(CreationEvType type, const std::string& attrType, int value, Object* sender) :
    Event(sender),
    type(type),
    attrType(attrType),
    value(value)
{}

CreationEvent::~CreationEvent() {}
