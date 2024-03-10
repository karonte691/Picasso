#include <PEngine/EventSystem/DeferredEventsStore.h>

#include <PEngine/EventSystem/EventFactory.h>

namespace Picasso::Engine::EventSystem
{
    DeferredEventsStore *DeferredEventsStore::Instance = nullptr;

    void DeferredEventsStore::Store(const PEvent event, const PEventData eventData)
    {
        std::lock_guard<std::mutex> lock(m_Mutex); // Lock for the scope of this function
        std::string eventName = EventFactory::PEventToString(event);
        m_EventsDataMap[eventName].push_back(eventData);
    }

    std::vector<PEventData> DeferredEventsStore::Consume(const PEvent event)
    {
        std::lock_guard<std::mutex> lock(m_Mutex); // Lock for the scope of this function
        std::string eventName = EventFactory::PEventToString(event);

        std::vector<PEventData> eventData = std::move(m_EventsDataMap[eventName]); // Move the vector to the return value

        m_EventsDataMap.erase(eventName); // Remove the empty vector to completely clear the entry

        return eventData;
    }
} // namespace Picasso::Engine::EventSystem