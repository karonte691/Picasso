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
#include <PEngine/EventSystem/Events/CameraUpdatePositionEvent.h>
#include <PEngine/EventSystem/Events/CameraUpdateViewEvent.h>
#include <PEngine/EventSystem/Events/RenderUpdateCameraViewEvent.h>
#include <PEngine/EventSystem/Events/RenderUpdateCameraPositionEvent.h>
#include <PEngine/EventSystem/Events/RendererUpdateMovementEvent.h>

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
        case PEvent::CAMERA_UPDATE_POSITION:
            return new Events::CameraUpdatePositionEvent();
        case PEvent::CAMERA_UPDATE_VIEW:
            return new Events::CameraUpdateViewEvent();
        case PEvent::RENDERER_UPDATE_CAMERA_VIEW:
            return new Events::RendererUpdateCameraViewEvent();
        case PEvent::RENDERER_UPDATE_CAMERA_POSITION:
            return new Events::RendererUpdateCameraPositionEvent();
        case PEvent::RENDER_UPDATE_MOVEMENT:
            return new Events::RendererUpdateMovementEvent();
        default:
            return nullptr;
        }
    }

    /**
     * @brief Convert the given event type to a string.
     * @param event The event type.
     * @return The string representation of the event type.
     */
    const std::string EventFactory::PEventToString(PEvent event)
    {
        switch (event)
        {
        case PEvent::APPLICATION_QUIT:
            return "APPLICATION_QUIT";
        case PEvent::RESIZED:
            return "RESIZED";
        case PEvent::PLATFORM_EXPOSE:
            return "PLATFORM_EXPOSE";
        case PEvent::CAMERA_UPDATE_VIEW:
            return "CAMERA_UPDATE_VIEW";
        case PEvent::CAMERA_UPDATE_POSITION:
            return "CAMERA_UPDATE_POSITION";
        case PEvent::RENDERER_UPDATE_CAMERA_VIEW:
            return "RENDERER_UPDATE_CAMERA_VIEW";
        case PEvent::RENDERER_UPDATE_CAMERA_POSITION:
            return "RENDERER_UPDATE_CAMERA_POSITION";
        case PEvent::RENDER_UPDATE_MOVEMENT:
            return "RENDER_UPDATE_MOVEMENT";
        case PEvent::KEY_PRESSED:
            return "KEY_PRESSED";
        case PEvent::KEY_RELEASED:
            return "KEY_RELEASED";
        case PEvent::BUTTON_PRESSED:
            return "BUTTON_PRESSED";
        case PEvent::BUTTON_RELEASED:
            return "BUTTON_RELEASED";
        case PEvent::MOUSE_MOVED:
            return "MOUSE_MOVED";
        case PEvent::MOUSE_WHEEL:
            return "MOUSE_WHEEL";
        case PEvent::CONTROLLER_MOVEMENT:
            return "CONTROLLER_MOVEMENT";
        case PEvent::CONTROLLER_SCALE:
            return "CONTROLLER_SCALE";
        default:
            return "UNKNOWN_EVENT";
        }
    }
} // namespace Picasso::Engine::EventSystem