#pragma once

#ifndef PLATFORM_EXPOSED_EVENT_H
#define PLATFORM_EXPOSED_EVENT_H

#include <PEngine/EventSystem/Events/BaseEvent.h>
#include <PEngine/EventSystem/Events/EventTypes.h>

namespace Picasso::Engine::EventSystem::Events
{
    class PlatformExposedEvent : public BaseEvent<PEvent>
    {
    public:
        PlatformExposedEvent() : BaseEvent<PEvent>(PEvent::PLATFORM_EXPOSE, "PlatformExposed"){};
        virtual ~PlatformExposedEvent() = default;
    };
}

#endif