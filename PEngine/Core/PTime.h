#pragma once

#ifndef P_TIME_H
#define P_TIME_H

#include <chrono>

namespace Picasso::Engine::Core
{
    enum PICASSO_TIME_STATE
    {
        NORMAL,
        SLEEP
    };

    class PTime
    {
    public:
        PTime();

        void StartDeltaTime();
        void EndDeltaTime();
        float GetRawDeltaTime();
        float GetDeltaTime();
        std::chrono::milliseconds GetSleepTime();

    private:
        std::chrono::system_clock::time_point m_startDeltaMoment;
        std::chrono::system_clock::time_point m_endDeltaMoment;
        std::chrono::duration<double, std::milli> m_rawDeltaTime;
        PICASSO_TIME_STATE m_state;
    };
}

#endif