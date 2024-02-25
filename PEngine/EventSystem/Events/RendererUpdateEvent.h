#pragma once

#ifndef RENDERER_UPDATE_EVENT_H
#define RENDERER_UPDATE_EVENT_H

#include <PEngine/EventSystem/Events/BaseEvent.h>

namespace Picasso::Engine::EventSystem::Events
{
    class RendererUpdateEvent : public BaseEvent<PEvent>
    {
    public:
        RendererUpdateEvent() : BaseEvent<PEvent>(PEvent::RENDERER_UPDATE, "RendererUpdate"){};
        virtual ~RendererUpdateEvent() = default;
    };
}

#endif // RENDERER_UPDATE_EVENT_H