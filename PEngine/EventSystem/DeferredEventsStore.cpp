/**
 * @file DeferredEventsStore.cpp
 * @brief Implementation of the DeferredEventsStore class.
 */
#include <PEngine/EventSystem/DeferredEventsStore.h>
#include <PEngine/EventSystem/EventFactory.h>

namespace Picasso::Engine::EventSystem
{
    DeferredEventsStore *DeferredEventsStore::Instance = nullptr;

    /**
     * @brief Stores the given event and its associated event data.
     * @param event The event to be stored.
     * @param eventData The event data to be associated with the event.
     */
    void DeferredEventsStore::Store(const PEvent event)
    {
        std::lock_guard<std::mutex> lock(m_Mutex); // Lock for the scope of this function
        std::string eventName = EventFactory::PEventToString(event);
        PEventData eventData; //@todo: This is a temporary fix. This should be removed once I figoure out how to empty events
        m_EventsDataMap[eventName].push_back(eventData);
    }

    /**
     * @brief Stores the given event and its associated event data.
     * @param event The event to be stored.
     * @param eventData The event data to be associated with the event.
     */
    void DeferredEventsStore::Store(const PEvent event, const PEventData eventData)
    {
        std::lock_guard<std::mutex> lock(m_Mutex); // Lock for the scope of this function
        std::string eventName = EventFactory::PEventToString(event);
        m_EventsDataMap[eventName].push_back(eventData);
    }

    /**
     * @brief Consumes and retrieves the event data associated with the given event.
     * @param event The event whose associated event data is to be consumed.
     * @return A vector containing the consumed event data.
     */
    std::vector<PEventData> DeferredEventsStore::Consume(const PEvent event)
    {
        std::lock_guard<std::mutex> lock(m_Mutex); // Lock for the scope of this function
        std::string eventName = EventFactory::PEventToString(event);

        std::vector<PEventData> eventData = std::move(m_EventsDataMap[eventName]); // Move the vector to the return value

        m_EventsDataMap.erase(eventName); // Remove the empty vector to completely clear the entry

        return eventData;
    }
} // namespace Picasso::Engine::EventSystem