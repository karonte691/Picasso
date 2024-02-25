#pragma once

#ifndef CONTROLLER_MOVE_EVENT_H
#define CONTROLLER_MOVE_EVENT_H

#include <PEngine/EventSystem/Events/BaseEvent.h>

namespace Picasso::Engine::EventSystem::Events
{
    class ControllerMoveEvent : public BaseEvent<PEvent>
    {
    public:
        ControllerMoveEvent() : BaseEvent<PEvent>(PEvent::CONTROLLER_MOVEMENT, "ControllerMove"){};
        virtual ~ControllerMoveEvent() = default;
    };
}

#endif // CONTROLLER_MOVE_EVENT_H