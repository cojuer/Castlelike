#pragma once

#include <list>
#include <unordered_map>
#include <typeindex>
#include <iostream>

#include "event.h"
#include "event_handler.h"
#include "handler_registration.h"

class EventBus : public Object
{
public:
    EventBus();

    virtual ~EventBus();

    static EventBus* GetInstance();

    template <class T>
    static HandlerRegistration* AddHandler(EventHandler<T>& handler, Object& sender);

    template <class T>
    static HandlerRegistration* AddHandler(EventHandler<T> & handler);

    static void FireEvent(Event& e);

private:
    static EventBus* instance;

    class EventRegistration : public HandlerRegistration
    {
        using Registrations = std::list<EventRegistration*>;
    
    public:
        EventRegistration(void* const handler, Registrations* const registrations, Object* const sender);

        virtual ~EventRegistration();

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
HandlerRegistration* EventBus::AddHandler(EventHandler<T>& handler, Object& sender)
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
HandlerRegistration* EventBus::AddHandler(EventHandler<T>& handler)
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
