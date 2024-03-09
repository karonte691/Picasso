#pragma once

#ifndef CAMERA_UPDATE_VIEW_EVENT_H
#define CAMERA_UPDATE_VIEW_EVENT_H

#include <PEngine/EventSystem/Events/BaseEvent.h>

namespace Picasso::Engine::EventSystem::Events
{
    class CameraUpdateViewEvent : public BaseEvent<PEvent>
    {
    public:
        CameraUpdateViewEvent() : BaseEvent<PEvent>(PEvent::CAMERA_UPDATE_VIEW, "CameraUpdateView"){};
        virtual ~CameraUpdateViewEvent() = default;
    };
}
#endif // CAMERA_UPDATE_VIEW_EVENT_H