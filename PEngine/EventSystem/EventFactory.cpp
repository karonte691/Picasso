/**
 * @file EventFactory.cpp
 * @brief Implementation of the EventFactory class.
 */

#include <PEngine/EventSystem/EventFactory.h>
#include <PEngine/EventSystem/Events/KeyPressedEvent.h>
#include <PEngine/EventSystem/Events/KeyReleasedEvent.h>
#include <PEngine/EventSystem/Events/ButtonReleasedEvent.h>
#include <PEngine/EventSystem/Events/ButtonPressedEvent.h>
#include <PEngine/EventSystem/Events/MouseMovedEvent.h>
#include <PEngine/EventSystem/Events/MouseWheelEvent.h>
#include <PEngine/EventSystem/Events/PlatformExposeEvent.h>
#include <PEngine/EventSystem/Events/ResizeEvent.h>
#include <PEngine/EventSystem/Events/ControllerMoveEvent.h>
#include <PEngine/EventSystem/Events/CameraUpdateEvent.h>
#include <PEngine/EventSystem/Events/RendererUpdateEvent.h>

#include <unordered_map>

namespace Picasso::Engine::EventSystem
{
    /**
     * @brief Get the corresponding event object based on the given event type.
     * @param event The event type.
     * @return A pointer to the corresponding event object, or nullptr if the event type is invalid.
     */
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
        case PEvent::CONTROLLER_MOVEMENT:
            return new Events::ControllerMoveEvent();
        case PEvent::CAMERA_UPDATE:
            return new Events::CameraUpdateEvent();
        case PEvent::RENDERER_UPDATE:
            return new Events::RendererUpdateEvent();
        default:
            return nullptr;
        }
    }
}