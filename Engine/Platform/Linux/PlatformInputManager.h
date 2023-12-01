#pragma once

#ifndef PLATFORM_INPUT_MANAGER_H
#define PLATFORM_INPUT_MANAGER_H

#include <xcb/xcb.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>
#include <sys/time.h>
#include <time.h>
#include <cstdlib>
#include <cstdio>
#include <memory>

#include <Engine/Logger.h>
#include <Engine/EventSystem/PERegistry.h>
#include <Engine/Input/Listener/KeyboardListener.h>
#include <Engine/Input/Listener/MouseListener.h>
#include <Engine/Input/InputState.h>
#include <Engine/Input/Translator/KeyCodeTranslator.h>
#include <Engine/Input/Translator/MouseCodeTranslator.h>
#include <Engine/Platform/Linux/LinuxPlatformInternalState.h>

namespace Picasso::Engine::Platform::Linux
{
    using Picasso::Engine::Input::pInputState;
    using Picasso::Engine::Input::Translators::KeyCodeTranslator;
    using Picasso::Engine::Input::Translators::MouseCodeTranslator;
    using Picasso::Engine::Input::Listener::KeyboardListener;
    using Picasso::Engine::Input::Listener::MouseListener;

    class PlatformInputManager
    {
        public:
            PlatformInputManager();

            void ProcessXCBKeyBoardEvent(xcb_generic_event_t* event, std::shared_ptr<LinuxPlatformInternalState> state, pInputState& inputState);
            void ProcessXCBMouseEvent(xcb_generic_event_t* event, std::shared_ptr<LinuxPlatformInternalState> state, pInputState& inputState);
            bool ProcessXCBClientMessage(xcb_generic_event_t* event, std::shared_ptr<LinuxPlatformInternalState> state);
        private:
            std::unique_ptr<KeyCodeTranslator> m_keyCodeTranslator;
            std::unique_ptr<MouseCodeTranslator> m_mouseCodeTranslator;
            std::unique_ptr<KeyboardListener> m_keyboardListener;
            std::unique_ptr<MouseListener> m_mouseListener;

    };
}

#endif