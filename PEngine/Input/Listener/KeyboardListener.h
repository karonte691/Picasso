#pragma once

#ifndef KEYBOARD_LISTENER_H
#define KEYBOARD_LISTENER_H

#include <PEngine/Logger/Logger.h>
#include <PEngine/EventSystem/PERegistry.h>
#include <PEngine/Input/Maps/Keyboard.h>
#include <PEngine/Input/InputState.h>


namespace Picasso::Engine::Input::Listener
{
    using Picasso::Engine::EventSystem::Events::PEvent;
    using Picasso::Engine::EventSystem::Events::PEventData;
    using Picasso::Engine::EventSystem::Events::BaseEvent;
    using Picasso::Engine::EventSystem::EventFactory;
    using Picasso::Engine::EventSystem::PicassoRegistry;
    using Picasso::Engine::Input::pInputState;
    
    class KeyboardListener
    {
        public:
            bool IsKeyDown(KEYS key, pInputState& inputState);
            bool IsKeyUp(KEYS key, pInputState& inputState);
            bool WasKeyDown(KEYS key, pInputState& inputState);
            bool WasKeyUp(KEYS key, pInputState& inputState);

            void ProcessKey(KEYS key, bool pressed, pInputState& inputState);
    };
}

#endif