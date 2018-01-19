#include "event.h"

Event::Event(Object* sender) :
    m_sender(sender),
    m_canceled(false)
{}

Event::~Event() = default;

void Event::setCanceled(bool canceled)
{
    m_canceled = canceled;
}

Object* Event::getSender() const
{
    return m_sender;
}

bool Event::isCanceled() const
{
    return m_canceled;
}