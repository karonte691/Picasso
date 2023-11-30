#pragma once

#ifndef PLATFORM_H
#define PLATFORM_H

#include <iostream>
#include <memory>

#include "../PBuild.h"
#include "../Logger.h"

#ifdef PICASSO_LINUX_BUILD
#include "Linux/LinuxPlatformInternalState.h"
#endif

namespace Picasso::Engine::Platform
{
    class PPlatform
    {
    public:
        bool Init(std::string appName, int x, int y, int width, int height);
        void Shutdown();
        bool Process();  
    private:

#ifdef PICASSO_LINUX_BUILD
        std::unique_ptr<LinuxPlatformInternalState> m_pstate;

        const std::string m_strWmDeleteWindow = "WM_DELETE_WINDOW";
        const std::string m_strWmProtocols = "WM_PROTOCOLS";
#endif
        int _getEventsMask() const;
        unsigned int _getEventsValue() const;
        void _registerWindowDestroyEvent();     
    };
}

#endif