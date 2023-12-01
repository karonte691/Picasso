#pragma once

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <iostream>
#include <functional>
#include <map>
#include <vector>
#include <memory>

#include "Events/BaseEvent.h"
#include "Events/EventTypes.h"
#include "EventFactory.h"
#include "../Logger.h"

namespace Picasso::Engine::EventSystem
{
    using Events::BaseEvent;
    using Events::PEvent;
    using Events::PEventData;

    class Dispatcher
    {
    public: 
        Dispatcher();

        using SlotType = std::function<void(std::shared_ptr<BaseEvent<PEvent>>&)>;
        static Dispatcher* Instance;

        void Subscribe(const PEvent& eventName, SlotType&& slot);
        void Post(const PEvent eventType, PEventData eventData) const;
    private:
        std::map<PEvent, std::vector<SlotType>, Events::BaseEventComparator> m_listeners;
        std::unique_ptr<EventFactory> m_eventFactory;
    };
}

#endif