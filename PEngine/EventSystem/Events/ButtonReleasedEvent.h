#pragma once

#ifndef BUTTON_RELEASED_EVENT
#define BUTTON_RELEASED_EVENT

#include <PEngine/EventSystem/Events/BaseEvent.h>
#include <PEngine/EventSystem/Events/EventTypes.h>

namespace Picasso::Engine::EventSystem::Events
{
    class ButtonReleasedEvent : public BaseEvent<PEvent>
    {
    public:
        ButtonReleasedEvent() : BaseEvent<PEvent>(PEvent::BUTTON_RELEASED, "ButtonReleased"){};
        virtual ~ButtonReleasedEvent() = default;
    };
}

#endif