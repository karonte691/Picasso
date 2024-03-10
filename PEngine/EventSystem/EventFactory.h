#pragma once

#ifndef EVENT_FACTORY_H
#define EVENT_FACTORY_H

#include <memory>
#include <string>

#include <PEngine/EventSystem/Events/BaseEvent.h>
#include <PEngine/EventSystem/Events/EventTypes.h>

namespace Picasso::Engine::EventSystem
{
    using Events::BaseEvent;
    using Events::PEvent;

    class EventFactory
    {
    public:
        BaseEvent<PEvent> *GetEvent(PEvent event);

        static const std::string PEventToString(PEvent event);
    };
}

#endif