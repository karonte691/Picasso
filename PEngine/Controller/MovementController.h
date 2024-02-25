#pragma once

#ifndef MOVEMENT_CONTROLLER_H
#define MOVEMENT_CONTROLLER_H

#include <PEngine/Controller/PicassoController.h>
#include <PEngine/EventSystem/PERegistry.h>
#include <PEngine/Math/Vector3.h>

namespace Picasso::Engine::Controller
{
    using Picasso::Engine::EventSystem::PicassoRegistry;
    using Picasso::Engine::EventSystem::Events::BaseEvent;
    using Picasso::Engine::EventSystem::Events::PEvent;

    class MovementController : public PicassoController
    {
    public:
        MovementController() : PicassoController("MovementController"){};
        bool InitController() override;

    private:
        Math::Vector3 m_Position;
        Math::Vector3 m_Rotation;
        void _onMovement(BaseEvent<PEvent> *&event);
    };
}

#endif // MOVEMENT_CONTROLLER_H