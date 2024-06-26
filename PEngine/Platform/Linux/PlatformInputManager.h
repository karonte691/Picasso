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

#include <PEngine/Logger/Logger.h>
#include <PEngine/EventSystem/PERegistry.h>
#include <PEngine/Input/Listener/KeyboardListener.h>
#include <PEngine/Input/Listener/MouseListener.h>
#include <PEngine/Input/InputState.h>
#include <PEngine/Input/Translator/KeyCodeTranslator.h>
#include <PEngine/Input/Translator/MouseCodeTranslator.h>
#include <PEngine/Platform/Linux/LinuxPlatformInternalState.h>

namespace Picasso::Engine::Platform::Linux
{
    using Picasso::Engine::Input::pInputState;
    using Picasso::Engine::Input::Listener::KeyboardListener;
    using Picasso::Engine::Input::Listener::MouseListener;
    using Picasso::Engine::Input::Translators::KeyCodeTranslator;
    using Picasso::Engine::Input::Translators::MouseCodeTranslator;

    class PlatformInputManager
    {
    public:
        PlatformInputManager();

        void ProcessXCBKeyBoardEvent(xcb_generic_event_t *event, LinuxPlatformInternalState *state, pInputState &inputState);
        void ProcessXCBMouseEvent(xcb_generic_event_t *event, LinuxPlatformInternalState *state, pInputState &inputState);
        void ProcessXCBMouseMovement(xcb_generic_event_t *event, pInputState &inputState);
        bool ProcessXCBClientMessage(xcb_generic_event_t *event, LinuxPlatformInternalState *state);

    private:
        std::unique_ptr<KeyCodeTranslator> m_keyCodeTranslator;
        std::unique_ptr<MouseCodeTranslator> m_mouseCodeTranslator;
        std::unique_ptr<KeyboardListener> m_keyboardListener;
        std::unique_ptr<MouseListener> m_mouseListener;
    };
}

#endif