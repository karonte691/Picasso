#pragma once

#ifndef DEFERRED_EVENTS_STORE_H
#define DEFERRED_EVENTS_STORE_H

#include <PEngine/EventSystem/Events/BaseEvent.h>

#include <vector>
#include <map>
#include <mutex>

namespace Picasso::Engine::EventSystem
{
    using Events::BaseEvent;
    using Events::PEvent;
    using Events::PEventData;

    class DeferredEventsStore
    {
    public:
        static DeferredEventsStore *Instance;

        void Store(const PEvent event);
        void Store(const PEvent event, const PEventData eventData);
        std::vector<PEventData> Consume(const PEvent event);

    private:
        std::map<std::string, std::vector<PEventData>> m_EventsDataMap;
        std::mutex m_Mutex; // Mutex for thread-safe access
    };
}

#endif // DEFERRED_EVENTS_STORE_H