#pragma once

#ifndef PLATFORM_H
#define PLATFORM_H

#include <iostream>
#include <memory>

#include <Engine/PBuild.h>
#include <Engine/Logger.h>
#include <Engine/EventSystem/PERegistry.h>

#ifdef PICASSO_LINUX_BUILD
#include <Engine/Platform/Linux/LinuxPlatformInternalState.h>

#include <Engine/Input/Translator/KeyCodeTranslator.h>
#include <Engine/Input/Translator/MouseCodeTranslator.h>
#include <Engine/Input/Listener/KeyboardListener.h>
#include <Engine/Input/Listener/MouseListener.h>
#include <Engine/Input/InputState.h>

#include <Engine/Platform/Linux/PlatformInputManager.h>
#endif

namespace Picasso::Engine::Platform
{
    using Picasso::Engine::Input::pInputState;

    
    class PPlatform
    {
    public:
        bool Init(std::string appName, int x, int y, int width, int height);
        void Shutdown();
        bool Process();  
    private:
        pInputState m_inputState;

#ifdef PICASSO_LINUX_BUILD
        std::shared_ptr<LinuxPlatformInternalState> m_pstate;
        std::unique_ptr<Picasso::Engine::Platform::Linux::PlatformInputManager> m_inputManager;

        const std::string m_strWmDeleteWindow = "WM_DELETE_WINDOW";
        const std::string m_strWmProtocols = "WM_PROTOCOLS";

        int _getEventsMask() const;
        unsigned int _getEventsValue() const;
        void _registerWindowDestroyEvent();   
#endif
    };
}

#endif