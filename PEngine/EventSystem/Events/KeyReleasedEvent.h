#pragma once

#ifndef KEY_RELEASED_EVENT
#define KEY_RELEASED_EVENT

#include <PEngine/EventSystem/Events/BaseEvent.h>
#include <PEngine/EventSystem/Events/EventTypes.h>

namespace Picasso::Engine::EventSystem::Events
{
    class KeyReleasedEvent : public BaseEvent<PEvent>
    {
    public:
        KeyReleasedEvent() : BaseEvent<PEvent>(PEvent::KEY_RELEASED, "keyReleased"){};
        virtual ~KeyReleasedEvent() = default;
    };
}

#endif