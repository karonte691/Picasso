#pragma once

#ifndef CLOCK_H
#define CLOCK_H

#include <bits/floatn-common.h>

namespace Picasso::Engine::Core
{
    struct ClockData
    {
        _Float64 startTime;
        _Float64 elapsed;
    };

    class Clock
    {
        public:
            void Start(ClockData* clockData, _Float64 pAbsoluteTime);
            void Update(ClockData* clockData, _Float64 pAbsoluteTime);
            void Stop(ClockData* clockData);
    };
}

#endif