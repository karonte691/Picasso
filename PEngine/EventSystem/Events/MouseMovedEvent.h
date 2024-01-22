#pragma once

#ifndef MOUSE_MOVED_EVENT
#define MOUSE_MOVED_EVENT

#include <PEngine/EventSystem/Events/BaseEvent.h>
#include <PEngine/EventSystem/Events/EventTypes.h>

namespace Picasso::Engine::EventSystem::Events
{
    class MouseMovementEvent : public BaseEvent<PEvent>
    {
    public:
        MouseMovementEvent() : BaseEvent<PEvent>(PEvent::MOUSE_MOVED, "MouseMoved"){};
        virtual ~MouseMovementEvent() = default;
    };
}

#endif