#pragma once

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <iostream>
#include <functional>
#include <map>
#include <vector>
#include <memory>

#include <PEngine/EventSystem/Events/BaseEvent.h>
#include <PEngine/EventSystem/Events/EventTypes.h>
#include <PEngine/EventSystem/EventFactory.h>
#include <PEngine/Logger/Logger.h>
#include <PEngine/Core/ThreadPool.h>

namespace Picasso::Engine::EventSystem
{
    using Events::BaseEvent;
    using Events::PEvent;
    using Events::PEventData;
    using SlotType = std::function<void(BaseEvent<PEvent> *&)>;

    struct SlotWrapper
    {
        SlotType slot;
        std::size_t id;

        SlotWrapper(SlotType slot, std::size_t id) : slot(std::move(slot)), id(id) {}
    };

    class Dispatcher
    {
    public:
        Dispatcher();

        static Dispatcher *Instance;

        std::size_t Subscribe(const PEvent &eventName, SlotType &&slot);
        void Unsubscribe(const PEvent &eventName, std::size_t slotId);
        void Post(const PEvent eventType) const;
        void Post(const PEvent eventType, PEventData eventData) const;

    private:
        std::map<PEvent, std::vector<SlotType>, Events::BaseEventComparator> m_Listeners;
        std::unique_ptr<EventFactory> m_EventFactory;
        std::unique_ptr<Core::ThreadPool> m_ThreadPool;

        std::size_t m_NextSlotId = 0;
    };
}

#endif