#include "EventFactory.h"
#include "Events/KeyPressedEvent.h"
#include "Events/KeyReleasedEvent.h"
#include "Events/ButtonReleasedEvent.h"
#include "Events/ButtonPressedEvent.h"


namespace Picasso::Engine::EventSystem
{
    std::shared_ptr<BaseEvent<PEvent>> EventFactory::GetEvent(PEvent event)
    {
        if(event == PEvent::KEY_PRESSED)
        {
            return std::make_shared<Events::KeyPressedEvent>();
        }

        if(event == PEvent::KEY_RELEASED)
        {
            return std::make_shared<Events::KeyReleasedEvent>();
        }

        if(event == PEvent::BUTTON_RELEASED)
        {
            return std::make_shared<Events::ButtonReleasedEvent>();
        }

        if(event == PEvent::BUTTON_PRESSED)
        {
            return std::make_shared<Events::ButtonPressedEvent>();
        }

        return nullptr;
    }
}