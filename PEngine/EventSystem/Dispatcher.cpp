/**
 * @file Dispatcher.cpp
 * @brief Implementation of the Dispatcher class.
 */

#include <PEngine/EventSystem/Dispatcher.h>

namespace Picasso::Engine::EventSystem
{
    using Events::BaseEvent;
    using Events::PEvent;
    using Events::PEventData;

    Dispatcher *Dispatcher::Instance = nullptr;

    /**
     * @brief Constructor for the Dispatcher class.
     */
    Dispatcher::Dispatcher()
    {
        m_eventFactory = std::make_unique<EventFactory>();
    }

    /**
     * @brief Subscribe a slot to a specific event.
     * @param eventName The event to subscribe to.
     * @param slot The slot to be called when the event is triggered.
     */
    void Dispatcher::Subscribe(const PEvent &eventName, SlotType &&slot)
    {
        m_listeners[eventName].push_back(slot);
    }

    /**
     * @brief Post an event without any event data.
     * @param eventType The type of event to post.
     */
    void Dispatcher::Post(const PEvent eventType) const
    {
        BaseEvent<PEvent> *event = m_eventFactory->GetEvent(eventType);

        if (!event)
        {
            Picasso::Engine::Logger::Logger::Fatal("Error while trying to factor event");
            return;
        }

        PEvent type = event->type();

        if (m_listeners.find(type) == m_listeners.end())
        {
            delete event;
            return;
        }

        auto &&observers = m_listeners.at(type);

        for (auto &&observer : observers)
        {
            observer(event);

            if (event->IsHandled())
            {
                break;
            }
        }

        delete event;
    }

    /**
     * @brief Post an event with event data.
     * @param eventType The type of event to post.
     * @param eventData The event data to be passed to the event handlers.
     */
    void Dispatcher::Post(const PEvent eventType, PEventData eventData) const
    {
        BaseEvent<PEvent> *event = m_eventFactory->GetEvent(eventType);

        if (!event)
        {
            Picasso::Engine::Logger::Logger::Fatal("Error while trying to factor event");
            return;
        }

        event->SetData(eventData);

        PEvent type = event->type();

        if (m_listeners.find(type) == m_listeners.end())
        {
            if (event != nullptr)
            {
                delete event;
            }
            return;
        }

        auto &&observers = m_listeners.at(type);

        for (auto &&observer : observers)
        {
            observer(event);

            if (event->IsHandled())
            {
                break;
            }
        }

        delete event;
    }
}