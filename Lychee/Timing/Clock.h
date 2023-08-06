#pragma once

/**
 * \brief A basic clock for keeping time.
 */
class Clock
{
    double m_time = 0.;
    bool m_isRunning = true;

public:
    /**
     * \brief The rate this clock is running at, relative to real-time.
     */
    double Rate = 1.;

    Clock() = default;

    /**
     * \brief Updates current time of this clock.
     * \param deltaTime Time since last frame, in milliseconds.
     */
    void Update(double deltaTime);
    /**
     * \brief Starts this clock.
     */
    void Start();
    /**
     * \brief Stops this clock.
     */
    void Stop();
    /**
     * \brief Sets the time of this clock to 0 and starts it.
     */
    void Restart();
    /**
     * \brief Sets the time of this clock to 0 and stops it.
     */
    void Reset();
    /**
     * \brief Adjusts this clock's time to the given time.
     * \param time The new time to seek to.
     */
    void SeekTo(double time);
    /**
     * \return Whether this clock is currently running or not.
     */
    bool GetIsRunning();
    /**
     * \return The current time of this clock, in milliseconds.
     */
    double GetTime();
};