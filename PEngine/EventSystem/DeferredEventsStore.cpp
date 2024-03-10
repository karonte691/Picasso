#include <PEngine/EventSystem/DeferredEventsStore.h>

#include <PEngine/EventSystem/EventFactory.h>

namespace Picasso::Engine::EventSystem
{
    DeferredEventsStore *DeferredEventsStore::Instance = nullptr;

    void DeferredEventsStore::Store(const PEvent event, const PEventData eventData)
    {
        std::string eventName = EventFactory::PEventToString(event);
        m_EventsDataMap[eventName].push_back(eventData);
    }

    std::vector<PEventData> DeferredEventsStore::Consume(const PEvent event)
    {
        std::string eventName = EventFactory::PEventToString(event);

        std::vector<PEventData> eventData = m_EventsDataMap[eventName];

        m_EventsDataMap[eventName].clear();

        return eventData;
    }
} // namespace Picasso::Engine::EventSystem