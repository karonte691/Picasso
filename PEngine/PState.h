#pragma once

#ifndef P_STATE_H
#define P_STATE_H

#include <memory>
#include <PEngine/Core/Clock.h>
#include <PEngine/PBuild.h>

#ifdef PICASSO_LINUX_BUILD
#include <PEngine/Platform/Linux/LinuxPlatformInternalState.h>
#endif

namespace Picasso::Engine
{
    using Picasso::Engine::Core::ClockData;
    using Picasso::Engine::Platform::LinuxPlatformInternalState;

    struct EngineState
    {
        bool running;
        bool suspended;
        int width;
        int height;
        ClockData *clockData;
        float lastTime;

        EngineState(bool run, bool suspend, int w, int h, float startTime, float elapsed, float last)
            : running(run), suspended(suspend), width(w), height(h), lastTime(last)
        {
            clockData = new ClockData{startTime, elapsed};
        }

        ~EngineState()
        {
            delete clockData;
        }
    };

    struct PPlatformState
    {
#ifdef PICASSO_LINUX_BUILD
        std::shared_ptr<LinuxPlatformInternalState> state;
#endif
    };
}

#endif