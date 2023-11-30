#pragma once

#ifndef KEYBOARD_LISTENER_H
#define KEYBOARD_LISTENER_H

#include "Logger.h"
#include "EventSystem/PERegistry.h"
#include "Input/Listener/Maps/Keyboard.h"
#include "Input/InputState.h"


namespace Picasso::Engine::Input::Listener
{
    using Picasso::Engine::EventSystem::Events::PEvent;
    using Picasso::Engine::EventSystem::Events::BaseEvent;
    using Picasso::Engine::EventSystem::EventFactory;
    using Picasso::Engine::EventSystem::PicassoRegistry;
    using Picasso::Engine::Input::pInputState;
    
    class KeyboardListener
    {
        public:
            bool IsKeyDown(KEYS key);
            bool IsKeyUp(KEYS key);
            bool WasKeyDown(KEYS key);
            bool WasKeyUp(KEYS key);

            void ProcessKey(KEYS key, bool pressed, pInputState& inputState);
    };
}

#endif