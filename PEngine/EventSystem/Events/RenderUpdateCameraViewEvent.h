#pragma once

#ifndef RENDERER_UPDATE_CAMERA_VIEW_EVENT_H
#define RENDERER_UPDATE_CAMERA_VIEW_EVENT_H

#include <PEngine/EventSystem/Events/BaseEvent.h>

namespace Picasso::Engine::EventSystem::Events
{
    class RendererUpdateCameraViewEvent : public BaseEvent<PEvent>
    {
    public:
        RendererUpdateCameraViewEvent() : BaseEvent<PEvent>(PEvent::RENDERER_UPDATE_CAMERA_VIEW, "RendererUpdateCameraView"){};
        virtual ~RendererUpdateCameraViewEvent() = default;
    };
}

#endif // RENDERER_UPDATE_CAMERA_VIEW_EVENT_H