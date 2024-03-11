#pragma once

#ifndef RENDERER_UPDATE_CAMERA_POSITION_EVENT_H
#define RENDERER_UPDATE_CAMERA_POSITION_EVENT_H

#include <PEngine/EventSystem/Events/BaseEvent.h>

namespace Picasso::Engine::EventSystem::Events
{
    class RendererUpdateCameraPositionEvent : public BaseEvent<PEvent>
    {
    public:
        RendererUpdateCameraPositionEvent() : BaseEvent<PEvent>(PEvent::RENDERER_UPDATE_CAMERA_POSITION, "RendererUpdateCameraPosition"){};
        virtual ~RendererUpdateCameraPositionEvent() = default;
    };
}

#endif // RENDERER_UPDATE_CAMERA_POSITION_EVENT_H