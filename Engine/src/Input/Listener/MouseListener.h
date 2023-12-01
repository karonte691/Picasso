#pragma once

#ifndef MOUSE_LISTENER_H
#define MOUSE_LISTENER_H

#include "EventSystem/PERegistry.h"
#include "Input/Listener/Maps/Mouse.h"
#include "Input/InputState.h"
#include "Maps/Mouse.h"

namespace Picasso::Engine::Input::Listener
{
    using Picasso::Engine::EventSystem::Events::BaseEvent;
    using Picasso::Engine::EventSystem::Events::PEvent;
    using Picasso::Engine::EventSystem::Events::PEventData;
    using Picasso::Engine::EventSystem::EventFactory;
    using Picasso::Engine::EventSystem::PicassoRegistry;
    using Picasso::Engine::Input::pInputState;

    class MouseListener
    {
        public:
            bool IsButtonUp(BUTTONS button, pInputState& inputState);
            bool IsButtonDown(BUTTONS button, pInputState& inputState);
            bool WasButtonUp(BUTTONS button, pInputState& inputState);
            bool WasButtonDown(BUTTONS button, pInputState& inputState);

            void GetMousePosition(float x, float y);
            void GetPrevMousePosition(float x, float y);

            void ProcessButton(BUTTONS button, bool pressed, pInputState& inputState);
            void ProcessMouseMove(float x, float y, pInputState& inputState);
            void ProcessMouseWheels(int zDelta);

    };
}

#endif