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
        m_EventFactory = std::make_unique<EventFactory>();
    }

    /**
     * @brief Subscribes a slot to the specified event.
     *
     * This function adds the specified slot to the list of listeners for the given event.
     *
     * @param eventName The event to subscribe to.
     * @param slot The slot to subscribe.
     * @return The unique identifier for the slot.
     */
    std::size_t Dispatcher::Subscribe(const PEvent &eventName, SlotType &&slot)
    {
        std::size_t slotId = m_NextSlotId++;
        m_Listeners[eventName].emplace_back(std::move(slot), slotId);
        return slotId;
    }

    /**
     * @brief Unsubscribes a listener from an event.
     *
     * This function removes a listener with the specified slotId from the list of listeners
     * associated with the given eventName. If the listeners list becomes empty after removing
     * the listener, the eventName is also removed from the map of listeners.
     *
     * @param eventName The event name to unsubscribe from.
     * @param slotId The ID of the listener slot to remove.
     */
    void Dispatcher::Unsubscribe(const PEvent &eventName, std::size_t slotId)
    {
        auto it = m_Listeners.find(eventName);

        if (it != m_Listeners.end())
        {
            auto &listenersForEvent = it->second;
            listenersForEvent.erase(std::remove_if(listenersForEvent.begin(), listenersForEvent.end(),
                                                   [slotId](const SlotWrapper &wrapper)
                                                   { return wrapper.id == slotId; }),
                                    listenersForEvent.end());

            if (listenersForEvent.empty())
            {
                m_Listeners.erase(it);
            }
        }
    }

    /**
     * @brief Post an event without any event data.
     * @param eventType The type of event to post.
     */
    void Dispatcher::Post(const PEvent eventType) const
    {

        BaseEvent<PEvent> *event = m_EventFactory->GetEvent(eventType);

        if (!event)
        {
            Picasso::Engine::Logger::Logger::Fatal("Error while trying to factor event");
            return;
        }

        PEvent type = event->type();

        auto it = m_Listeners.find(type);
        if (it == m_Listeners.end())
        {
            delete event;
            return;
        }

        for (auto &&observer : it->second)
        {
            observer.callback(event);

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
        BaseEvent<PEvent> *event = m_EventFactory->GetEvent(eventType);

        if (!event)
        {
            Picasso::Engine::Logger::Logger::Fatal("Error while trying to factor event");
            return;
        }

        event->SetData(eventData);

        PEvent type = event->type();

        if (m_Listeners.find(type) == m_Listeners.end())
        {
            if (event != nullptr)
            {
                delete event;
            }
            return;
        }

        auto &&observers = m_Listeners.at(type);

        for (auto &&observer : observers)
        {
            observer.callback(event);

            if (event->IsHandled())
            {
                break;
            }
        }

        delete event;
    }

}