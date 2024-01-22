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
    using EventMap = std::unordered_map<PEvent, std::shared_ptr<BaseEvent<PEvent>>>;

    std::shared_ptr<BaseEvent<PEvent>> EventFactory::GetEvent(PEvent event)
    {
        static const EventMap eventMap = {
            {PEvent::KEY_PRESSED, std::make_shared<Events::KeyPressedEvent>()},
            {PEvent::KEY_RELEASED, std::make_shared<Events::KeyReleasedEvent>()},
            {PEvent::BUTTON_RELEASED, std::make_shared<Events::ButtonReleasedEvent>()},
            {PEvent::BUTTON_PRESSED, std::make_shared<Events::ButtonPressedEvent>()},
            {PEvent::MOUSE_MOVED, std::make_shared<Events::MouseMovementEvent>()},
            {PEvent::MOUSE_WHEEL, std::make_shared<Events::MouseWheelEvent>()},
            {PEvent::PLATFORM_EXPOSE, std::make_shared<Events::PlatformExposedEvent>()}

        };

        const auto &it = eventMap.find(event);
        if (it != eventMap.end())
        {
            return it->second;
        }

        return nullptr;
    }
}