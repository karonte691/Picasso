#pragma once

#ifndef CAMERA_UPDATE_EVENT_H
#define CAMERA_UPDATE_EVENT_H

#include <PEngine/EventSystem/Events/BaseEvent.h>

namespace Picasso::Engine::EventSystem::Events
{
    class CameraUpdateEvent : public BaseEvent<PEvent>
    {
    public:
        CameraUpdateEvent() : BaseEvent<PEvent>(PEvent::CAMERA_UPDATE, "CameraUpdate"){};
        virtual ~CameraUpdateEvent() = default;
    };
}
#endif // CAMERA_UPDATE_EVENT_H