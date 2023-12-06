#include <PEngine/Core/PTime.h>

namespace Picasso::Engine::Core
{
    PTime::PTime()
    {
        m_state = NORMAL;
    }

    void PTime::StartDeltaTime()
    {
        m_startDeltaMoment = std::chrono::system_clock::now();
    }

    void PTime::EndDeltaTime()
    {
        m_endDeltaMoment = std::chrono::system_clock::now();
    }

    float PTime::GetRawDeltaTime()
    {
        m_rawDeltaTime = m_endDeltaMoment - m_startDeltaMoment;
        return m_rawDeltaTime.count();
    }

    float PTime::GetDeltaTime()
    {
        if (m_state == NORMAL)
        {
            // Picasso didn't reached the ms limit, so we return the prev deltaTime value
            return m_rawDeltaTime.count();
        }

        // reset the end
        this->EndDeltaTime();
        std::chrono::duration<double, std::milli> sleepTime = m_endDeltaMoment - m_startDeltaMoment;

        m_state = NORMAL;

        return m_rawDeltaTime.count() + sleepTime.count();
    }

    std::chrono::milliseconds PTime::GetSleepTime()
    {
        // if we are here, that means that the frame time reacher the ms limit defined in PBuild.h
        // so we should switch the to state of time to sleep mode for further ops
        m_state = SLEEP;

        std::chrono::duration<double, std::milli> frameTime = m_endDeltaMoment - m_startDeltaMoment;
        std::chrono::duration<double, std::milli> sleepTime(200.0 - frameTime.count());

        auto sleepDuration = std::chrono::duration_cast<std::chrono::milliseconds>(sleepTime);

        return std::chrono::milliseconds(sleepDuration.count());
    }
}