#include "EventFactory.h"
#include "Events/KeyPressedEvent.h"
#include "Events/KeyReleasedEvent.h"
#include "Events/ButtonReleasedEvent.h"
#include "Events/ButtonPressedEvent.h"
#include "Events/MouseMovedEvent.h"
#include "Events/MouseWheelEvent.h"

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
            {PEvent::MOUSE_WHEEL, std::make_shared<Events::MouseWheelEvent>()}
        };

        const auto& it = eventMap.find(event);
        if (it != eventMap.end()) {
            return it->second;
        }

        return nullptr;
    }
}