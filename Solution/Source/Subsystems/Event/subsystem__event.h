#pragma once

#include <list>
#include <unordered_map>
#include <typeindex>
#include <iostream>

#include "event.h"
#include "event_handler.h"
#include "handler_registration.h"

class EventSubsystem : public Object
{
public:
    EventSubsystem();

    virtual ~EventSubsystem();

    static EventSubsystem* GetInstance();

    template <class T>
    static HandlerRegistration* AddHandler(EventHandler<T>& handler, Object& sender);

    template <class T>
    static HandlerRegistration* AddHandler(EventHandler<T> & handler);

    static void FireEvent(Event& e);

private:
    static EventSubsystem* s_instance;

    class EventRegistration : public HandlerRegistration
    {
        using Registrations = std::list<EventRegistration*>;
    
    public:
        EventRegistration(void* handler, Registrations* registrations, Object* sender);

        EventRegistration(const EventRegistration&) = delete;
        EventRegistration(EventRegistration&&) = delete;
        EventRegistration& operator=(const EventRegistration&) = delete;
        EventRegistration& operator=(EventRegistration&&) = delete;

        virtual ~EventRegistration() = default;

        void*   getHandler() const;
        Object* getSender() const;

        void removeHandler() override;

    private:
        void* const          m_handler;
        Registrations* const m_registrations;
        Object* const        m_sender;
        bool                 m_registered;
    };

    typedef std::list<EventRegistration*> Registrations;
    typedef std::unordered_map<std::type_index, std::list<EventRegistration*>*> TypeMap;

    TypeMap handlers;
};

template <class T>
HandlerRegistration* EventSubsystem::AddHandler(EventHandler<T>& handler, Object& sender)
{
    auto instance = GetInstance();

    auto registrations = instance->handlers[typeid(T)];

    if (registrations == nullptr)
    {
        registrations = new Registrations();
        instance->handlers[typeid(T)] = registrations;
    }

    auto registration = new EventRegistration(static_cast<void*>(&handler), registrations, &sender);
    registrations->push_back(registration);
    return registration;
}

template <class T>
HandlerRegistration* EventSubsystem::AddHandler(EventHandler<T>& handler)
{
    auto instance = GetInstance();
    auto registrations = instance->handlers[typeid(T)];

    if (registrations == nullptr)
    {
        registrations = new Registrations();
        instance->handlers[typeid(T)] = registrations;
    }

    auto registration = new EventRegistration(static_cast<void*>(&handler), registrations, nullptr);
    registrations->push_back(registration);
    return registration;
}
