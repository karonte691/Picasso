#include <PEngine/Core/Clock.h>

namespace Picasso::Engine::Core
{
    void Clock::Start(ClockData *clockData, float pAbsoluteTime)
    {
        clockData->startTime = pAbsoluteTime;
        clockData->elapsed = 0;
    }

    void Clock::Update(ClockData *clockData, float pAbsoluteTime)
    {
        if (clockData->startTime == 0)
        {
            return;
        }

        clockData->elapsed = pAbsoluteTime - clockData->startTime;
    }

    void Clock::Stop(ClockData *clockData)
    {
        clockData->startTime = 0;
    }
}