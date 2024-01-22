#pragma once

#ifndef BUTTON_PRESSED_EVENT
#define BUTTON_PRESSED_EVENT

#include <PEngine/EventSystem/Events/BaseEvent.h>
#include <PEngine/EventSystem/Events/EventTypes.h>

namespace Picasso::Engine::EventSystem::Events
{
    class ButtonPressedEvent : public BaseEvent<PEvent>
    {
    public:
        ButtonPressedEvent() : BaseEvent<PEvent>(PEvent::BUTTON_PRESSED, "ButtonPressed"){};
        virtual ~ButtonPressedEvent() = default;
    };
}

#endif