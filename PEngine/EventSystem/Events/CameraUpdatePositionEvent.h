#pragma once

#ifndef CAMERA_UPDATE_POSITION_EVENT_H
#define CAMERA_UPDATE_POSITION_EVENT_H

#include <PEngine/EventSystem/Events/BaseEvent.h>

namespace Picasso::Engine::EventSystem::Events
{
    class CameraUpdatePositionEvent : public BaseEvent<PEvent>
    {
    public:
        CameraUpdatePositionEvent() : BaseEvent<PEvent>(PEvent::CAMERA_UPDATE_VIEW, "CameraUpdatePosition"){};
        virtual ~CameraUpdatePositionEvent() = default;
    };
}
#endif // CAMERA_UPDATE_POSITION_EVENT_H