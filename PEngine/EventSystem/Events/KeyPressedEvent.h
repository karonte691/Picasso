#pragma once

#ifndef KEY_PRESSED_EVENT
#define KEY_PRESSED_EVENT

#include "BaseEvent.h"
#include "EventTypes.h"

namespace Picasso::Engine::EventSystem::Events
{
    class KeyPressedEvent : public BaseEvent<PEvent>
    {
        public:
            KeyPressedEvent() : BaseEvent<PEvent>(PEvent::KEY_PRESSED, "keyPressed"){};
            virtual ~KeyPressedEvent() = default;
    };
}

#endif