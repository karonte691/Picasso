#pragma once

#ifndef RESIZE_EVENT_H
#define RESIZE_EVENT_H

#include <PEngine/EventSystem/Events/BaseEvent.h>
#include <PEngine/EventSystem/Events/EventTypes.h>

namespace Picasso::Engine::EventSystem::Events
{
    class ResizeEvent : public BaseEvent<PEvent>
    {
    public:
        ResizeEvent() : BaseEvent<PEvent>(PEvent::RESIZED, "Resize"){};
        virtual ~ResizeEvent() = default;
    };
}

#endif