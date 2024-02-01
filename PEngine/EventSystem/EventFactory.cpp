#include <PEngine/EventSystem/EventFactory.h>
#include <PEngine/EventSystem/Events/KeyPressedEvent.h>
#include <PEngine/EventSystem/Events/KeyReleasedEvent.h>
#include <PEngine/EventSystem/Events/ButtonReleasedEvent.h>
#include <PEngine/EventSystem/Events/ButtonPressedEvent.h>
#include <PEngine/EventSystem/Events/MouseMovedEvent.h>
#include <PEngine/EventSystem/Events/MouseWheelEvent.h>
#include <PEngine/EventSystem/Events/PlatformExposeEvent.h>

#include <unordered_map>

namespace Picasso::Engine::EventSystem
{
    using EventMap = std::unordered_map<PEvent, BaseEvent<PEvent> *>;

    BaseEvent<PEvent> *EventFactory::GetEvent(PEvent event)
    {
        static const EventMap eventMap = {
            {PEvent::KEY_PRESSED, new Events::KeyPressedEvent()},
            {PEvent::KEY_RELEASED, new Events::KeyReleasedEvent()},
            {PEvent::BUTTON_RELEASED, new Events::ButtonReleasedEvent()},
            {PEvent::BUTTON_PRESSED, new Events::ButtonPressedEvent()},
            {PEvent::MOUSE_MOVED, new Events::MouseMovementEvent()},
            {PEvent::MOUSE_WHEEL, new Events::MouseWheelEvent()},
            {PEvent::PLATFORM_EXPOSE, new Events::PlatformExposedEvent}

        };

        const auto &it = eventMap.find(event);
        if (it != eventMap.end())
        {
            return it->second;
        }

        return nullptr;
    }
}