#include "Clock.h"

void Clock::Update(double deltaTime)
{
    if (!m_isRunning)
        return;

    m_time += deltaTime * Rate;
}

void Clock::Start()
{
    m_isRunning = true;
}

void Clock::Stop()
{
    m_isRunning = false;
}

void Clock::Restart()
{
    m_time = 0.;
    m_isRunning = true;
}

void Clock::Reset()
{
    m_time = 0.;
    m_isRunning = false;
}

void Clock::SeekTo(double time)
{
    m_time = time;
}

bool Clock::GetIsRunning()
{
    return m_isRunning;
}

double Clock::GetTime()
{
    return m_time;
}
