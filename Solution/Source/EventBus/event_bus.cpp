#include "event_bus.h"

EventBus* EventBus::instance = nullptr;

EventBus::EventRegistration::EventRegistration(void* const handler, Registrations* const registrations, Object* const sender) :
    m_handler(handler),
    m_registrations(registrations),
    m_sender(sender),
    m_registered(true)
{}

EventBus::EventRegistration::~EventRegistration() = default;

void* EventBus::EventRegistration::getHandler() const
{
    return m_handler;
}

Object* EventBus::EventRegistration::getSender() const
{
    return m_sender;
}

void EventBus::EventRegistration::removeHandler()
{
    if (m_registered) 
    {
        m_registrations->remove(this);
        m_registered = false;
    }
}

EventBus::EventBus() = default;

EventBus::~EventBus() = default;

EventBus* EventBus::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new EventBus();
    }

    return instance;
}

void EventBus::FireEvent(Event& e)
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
