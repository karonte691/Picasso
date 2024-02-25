#pragma once

#ifndef MOVEMENT_CONTROLLER_H
#define MOVEMENT_CONTROLLER_H

#include <PEngine/Controller/PicassoController.h>
#include <PEngine/EventSystem/PERegistry.h>

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
        void _onMovement(BaseEvent<PEvent> *&event);
    };
}

#endif // MOVEMENT_CONTROLLER_H