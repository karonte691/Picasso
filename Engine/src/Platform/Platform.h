#pragma once

#ifndef PLATFORM_H
#define PLATFORM_H

#include <iostream>
#include <memory>

#include "../PBuild.h"
#include "../Logger.h"

#include "../EventSystem/PERegistry.h"

#ifdef PICASSO_LINUX_BUILD
#include "Linux/LinuxPlatformInternalState.h"
#include "../Input/Translator/KeyCodeTranslator.h"
#include "../Input/Listener/KeyboardListener.h"
#include "../Input/Listener/MouseListener.h"
#include "../Input/InputState.h"
#endif

namespace Picasso::Engine::Platform
{
    using Picasso::Engine::Input::Translators::KeyCodeTranslator;
    using Picasso::Engine::Input::Listener::KeyboardListener;
    using Picasso::Engine::Input::pInputState;
    
    class PPlatform
    {
    public:
        bool Init(std::string appName, int x, int y, int width, int height);
        void Shutdown();
        bool Process();  
    private:

#ifdef PICASSO_LINUX_BUILD
        std::unique_ptr<LinuxPlatformInternalState> m_pstate;
        std::unique_ptr<KeyCodeTranslator> m_keyCodeTranslator;
        std::unique_ptr<KeyboardListener> m_keyboardListener;

        pInputState m_inputState;

        const std::string m_strWmDeleteWindow = "WM_DELETE_WINDOW";
        const std::string m_strWmProtocols = "WM_PROTOCOLS";
#endif
        int _getEventsMask() const;
        unsigned int _getEventsValue() const;
        void _registerWindowDestroyEvent();     
    };
}

#endif