#pragma once

#ifndef MOVEMENT_CONTROLLER_H
#define MOVEMENT_CONTROLLER_H

#include <PEngine/Controller/PicassoController.h>
#include <PEngine/EventSystem/PERegistry.h>
#include <PEngine/Math/Vector3.h>
#include <PEngine/Input/InputState.h>
#include <PEngine/PBuild.h>

#include <string>

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
        void Update() override;

    private:
        Math::Vector3 m_Position;
        Math::Vector3 m_Rotation;
        bool m_IsPressed;
        Input::InputDirection m_CurrentDirection;

        void _UpdateInputState(const EventSystem::Events::PEventData &eData);
        void _DispatchUpdate();
        void _onMovement(BaseEvent<PEvent> *&event);

#if PICASSO_DEBUG_ENABLE
        std::string _DebugPrintPosition(Input::InputDirection direction);
#endif
    };
}

#endif // MOVEMENT_CONTROLLER_H