#pragma once

#ifndef KEY_PRESSED_EVENT
#define KEY_PRESSED_EVENT

#include <PEngine/EventSystem/Events/BaseEvent.h>
#include <PEngine/EventSystem/Events/EventTypes.h>

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