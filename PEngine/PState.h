#pragma once

#ifndef P_STATE_H
#define P_STATE_H

#include <PEngine/Core/Clock.h>

namespace Picasso::Engine
{
    using Picasso::Engine::Core::ClockData;

    struct EngineState
    {
        bool running;
        bool suspended;
        int width;
        int height;
        ClockData* clockData;
        float lastTime;

        EngineState(bool run, bool suspend, int w, int h, double startTime, double elapsed, float last)
        : running(run), suspended(suspend), width(w), height(h), lastTime(last)
        {
            clockData = new ClockData{startTime, elapsed};
        }
        
        ~EngineState()
        {
            delete clockData;
        }
    };
}

#endif