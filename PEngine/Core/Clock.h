#pragma once

#ifndef CLOCK_H
#define CLOCK_H

namespace Picasso::Engine::Core
{
    struct ClockData
    {
        float startTime;
        float elapsed;
    };

    class Clock
    {
    public:
        void Start(ClockData *clockData, float pAbsoluteTime);
        void Update(ClockData *clockData, float pAbsoluteTime);
        void Stop(ClockData *clockData);
    };
}

#endif