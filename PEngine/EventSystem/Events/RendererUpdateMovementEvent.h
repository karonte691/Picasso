#pragma once

#ifndef RENDERER_UPDATE_MOVEMENT_EVENT_H
#define RENDERER_UPDATE_MOVEMENT_EVENT_H

#include <PEngine/EventSystem/Events/BaseEvent.h>

namespace Picasso::Engine::EventSystem::Events
{
    class RendererUpdateMovementEvent : public BaseEvent<PEvent>
    {
    public:
        RendererUpdateMovementEvent() : BaseEvent<PEvent>(PEvent::RENDER_UPDATE_MOVEMENT, "RendererUpdateMovement"){};
        virtual ~RendererUpdateMovementEvent() = default;
    };
}

#endif // RENDERER_UPDATE_EVENT_H