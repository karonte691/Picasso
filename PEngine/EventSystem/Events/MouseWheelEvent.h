#pragma once

#ifndef MOUSE_WHEEL_EVENT
#define MOUSE_WHEEL_EVENT

#include <PEngine/EventSystem/Events/BaseEvent.h>
#include <PEngine/EventSystem/Events/EventTypes.h>

namespace Picasso::Engine::EventSystem::Events
{
    class MouseWheelEvent : public BaseEvent<PEvent>
    {
    public:
        MouseWheelEvent() : BaseEvent<PEvent>(PEvent::MOUSE_WHEEL, "MouseWheel"){};
        virtual ~MouseWheelEvent() = default;
    };
}

#endif