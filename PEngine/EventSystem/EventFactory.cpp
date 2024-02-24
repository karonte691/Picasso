#include <PEngine/EventSystem/EventFactory.h>
#include <PEngine/EventSystem/Events/KeyPressedEvent.h>
#include <PEngine/EventSystem/Events/KeyReleasedEvent.h>
#include <PEngine/EventSystem/Events/ButtonReleasedEvent.h>
#include <PEngine/EventSystem/Events/ButtonPressedEvent.h>
#include <PEngine/EventSystem/Events/MouseMovedEvent.h>
#include <PEngine/EventSystem/Events/MouseWheelEvent.h>
#include <PEngine/EventSystem/Events/PlatformExposeEvent.h>
#include <PEngine/EventSystem/Events/ResizeEvent.h>

#include <unordered_map>

namespace Picasso::Engine::EventSystem
{
    BaseEvent<PEvent> *EventFactory::GetEvent(PEvent event)
    {
        switch (event)
        {
        case PEvent::KEY_PRESSED:
            return new Events::KeyPressedEvent();
        case PEvent::KEY_RELEASED:
            return new Events::KeyReleasedEvent();
        case PEvent::BUTTON_RELEASED:
            return new Events::ButtonReleasedEvent();
        case PEvent::BUTTON_PRESSED:
            return new Events::ButtonPressedEvent();
        case PEvent::MOUSE_MOVED:
            return new Events::MouseMovementEvent();
        case PEvent::MOUSE_WHEEL:
            return new Events::MouseWheelEvent();
        case PEvent::PLATFORM_EXPOSE:
            return new Events::PlatformExposedEvent();
        case PEvent::RESIZED:
            return new Events::ResizeEvent();
        default:
            return nullptr;
        }
    }
}