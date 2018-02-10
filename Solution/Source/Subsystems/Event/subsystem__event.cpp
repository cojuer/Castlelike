#include "subsystem__event.h"

EventSubsystem* EventSubsystem::s_instance = nullptr;

EventSubsystem::EventRegistration::EventRegistration(void* handler, Registrations* registrations, Object* sender) :
    m_handler(handler),
    m_registrations(registrations),
    m_sender(sender),
    m_registered(true)
{}

void* EventSubsystem::EventRegistration::getHandler() const
{
    return m_handler;
}

Object* EventSubsystem::EventRegistration::getSender() const
{
    return m_sender;
}

void EventSubsystem::EventRegistration::removeHandler()
{
    if (m_registered) 
    {
        m_registrations->remove(this);
        m_registered = false;
    }
}

EventSubsystem::EventSubsystem() = default;

EventSubsystem::~EventSubsystem() = default;

EventSubsystem* EventSubsystem::GetInstance()
{
    if (s_instance == nullptr)
    {
        s_instance = new EventSubsystem();
    }

    return s_instance;
}

void EventSubsystem::FireEvent(Event& e)
{
    auto instance = GetInstance();

    auto registrations = instance->handlers[typeid(e)];

    if (registrations == nullptr)
    {
        return;
    }

    for (auto & reg : *registrations)
    {
        static_cast<EventHandler<Event>*>(reg->getHandler())->dispatch(e);
    }
}
