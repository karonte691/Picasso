#include <PEngine/Core/PTime.h>
#include <PEngine/PBuild.h>

/**
 * @brief PTime class implementation for time management.
 */
namespace Picasso::Engine::Core
{
    /**
     * @brief Default constructor for PTime class.
     * Initializes the state to NORMAL.
     */
    PTime::PTime()
    {
        m_state = NORMAL;
    }

    /**
     * @brief Start measuring the delta time.
     * Sets the start delta moment to the current system time.
     */
    void PTime::StartDeltaTime()
    {
        m_startDeltaMoment = std::chrono::system_clock::now();
    }

    /**
     * @brief End measuring the delta time.
     * Sets the end delta moment to the current system time.
     */
    void PTime::EndDeltaTime()
    {
        m_endDeltaMoment = std::chrono::system_clock::now();
    }

    /**
     * @brief Get the raw delta time in seconds.
     * Calculates the raw delta time by subtracting the start delta moment from the end delta moment.
     * @return The raw delta time in seconds.
     */
    float PTime::GetRawDeltaTime()
    {
        m_rawDeltaTime = m_endDeltaMoment - m_startDeltaMoment;
        return m_rawDeltaTime.count();
    }

    /**
     * @brief Get the delta time in seconds.
     * If the state is NORMAL, returns the raw delta time.
     * If the state is SLEEP, calculates the sleep time and adds it to the raw delta time.
     * @return The delta time in seconds.
     */
    float PTime::GetDeltaTime()
    {
        if (m_state == NORMAL)
        {
            // Picasso didn't reach the ms limit, so we return the previous delta time value
            return m_rawDeltaTime.count();
        }

        // Reset the end delta moment
        this->EndDeltaTime();
        std::chrono::duration<double, std::milli> sleepTime = m_endDeltaMoment - m_startDeltaMoment;

        m_state = NORMAL;

        return m_rawDeltaTime.count() + sleepTime.count();
    }

    /**
     * @brief Get the sleep time in milliseconds.
     * If the frame time reaches the ms limit defined in PBuild.h,
     * switches the state of time to sleep mode for further operations.
     * Calculates the sleep time by subtracting the frame time from the ms limit.
     * @return The sleep time in milliseconds.
     */
    std::chrono::milliseconds PTime::GetSleepTime()
    {
        m_state = SLEEP;

        std::chrono::duration<double, std::milli> frameTime = m_endDeltaMoment - m_startDeltaMoment;
        std::chrono::duration<double, std::milli> sleepTime(PICASSO_FRAME_MS_LIMIT - frameTime.count());

        auto sleepDuration = std::chrono::duration_cast<std::chrono::milliseconds>(sleepTime);

        return std::chrono::milliseconds(sleepDuration.count());
    }
}