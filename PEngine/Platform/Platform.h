#pragma once

#ifndef PLATFORM_H
#define PLATFORM_H

#include <iostream>
#include <memory>

#include <PEngine/PBuild.h>
#include <PEngine/Logger.h>
#include <PEngine/EventSystem/PERegistry.h>

#ifdef PICASSO_LINUX_BUILD
#include <PEngine/Platform/Linux/LinuxPlatformInternalState.h>

#include <PEngine/Input/Translator/KeyCodeTranslator.h>
#include <PEngine/Input/Translator/MouseCodeTranslator.h>
#include <PEngine/Input/Listener/KeyboardListener.h>
#include <PEngine/Input/Listener/MouseListener.h>
#include <PEngine/Input/InputState.h>

#include <PEngine/Platform/Linux/PlatformInputManager.h>
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
        void Suspend(u_int64_t ms);
        _Float64 GetAbsoluteTime();
        
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