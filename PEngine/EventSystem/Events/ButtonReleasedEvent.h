#pragma once

#ifndef BUTTON_RELEASED_EVENT
#define BUTTON_RELEASED_EVENT

#include "BaseEvent.h"
#include "EventTypes.h"

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