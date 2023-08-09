#include "TransformationSequence.h"

#include "../Graphics/Drawable.h"

TransformationSequence::TransformationSequence(Drawable* drawable)
{
    m_drawable = drawable;
}

void TransformationSequence::ApplyTransformations()
{
    const double time = m_drawable->GetClock()->GetTime();

    for (const std::shared_ptr<Transformation>& transformation : m_sequence)
        transformation->Apply(time);
}

void TransformationSequence::FinishTransformations()
{
    for (const std::shared_ptr<Transformation>& transformation : m_sequence)
        transformation->Finish();
}

TransformationSequence& TransformationSequence::FadeIn(double duration, Easing easing)
{
    const double startTime = std::max((m_drawable->GetLoadState() == LoadState::Loaded ? m_drawable->GetClock()->GetTime() : 0.), m_nextMinimumStartTime);
    const double endTime = startTime + duration;

    if (startTime < m_minStartTime)
        m_minStartTime = endTime;

    if (endTime > m_maxEndTime)
        m_maxEndTime = endTime;

    m_delay = 0;
    m_nextMinimumStartTime = 0.;

    const auto transformation = std::make_shared<Transformation>(m_drawable, TransformationType::Alpha, easing, startTime, endTime, 1.f);
    m_sequence.push_back(transformation);

    return *this;
}

TransformationSequence& TransformationSequence::FadeOut(double duration, Easing easing)
{
    const double startTime = std::max((m_drawable->GetLoadState() == LoadState::Loaded ? m_drawable->GetClock()->GetTime() : 0.), m_nextMinimumStartTime);
    const double endTime = startTime + duration;

    if (startTime < m_minStartTime)
        m_minStartTime = endTime;

    if (endTime > m_maxEndTime)
        m_maxEndTime = endTime;

    m_delay = 0;
    m_nextMinimumStartTime = 0.;

    const auto transformation = std::make_shared<Transformation>(m_drawable, TransformationType::Alpha, easing, startTime, endTime, 0.f);
    m_sequence.push_back(transformation);

    return *this;
}

TransformationSequence& TransformationSequence::FadeTo(float newAlpha, double duration, Easing easing)
{
    const double startTime = std::max((m_drawable->GetLoadState() == LoadState::Loaded ? m_drawable->GetClock()->GetTime() : 0.), m_nextMinimumStartTime);
    const double endTime = startTime + duration;

    if (startTime < m_minStartTime)
        m_minStartTime = endTime;

    if (endTime > m_maxEndTime)
        m_maxEndTime = endTime;

    m_delay = 0;
    m_nextMinimumStartTime = 0.;

    const auto transformation = std::make_shared<Transformation>(m_drawable, TransformationType::Alpha, easing, startTime, endTime, newAlpha);
    m_sequence.push_back(transformation);

    return *this;
}

TransformationSequence& TransformationSequence::FadeInFromZero(double duration, Easing easing)
{
    const double startTime = std::max((m_drawable->GetLoadState() == LoadState::Loaded ? m_drawable->GetClock()->GetTime() : 0.), m_nextMinimumStartTime);
    const double endTime = startTime + duration;

    if (startTime < m_minStartTime)
        m_minStartTime = endTime;

    if (endTime > m_maxEndTime)
        m_maxEndTime = endTime;

    m_delay = 0;
    m_nextMinimumStartTime = 0.;

    const auto fadeOutTransformation = std::make_shared<Transformation>(m_drawable, TransformationType::Alpha, easing, startTime, startTime, 0.f);
    m_sequence.push_back(fadeOutTransformation);

    const auto transformation = std::make_shared<Transformation>(m_drawable, TransformationType::Alpha, easing, startTime, endTime, 1.f);
    m_sequence.push_back(transformation);

    return *this;
}

TransformationSequence& TransformationSequence::FadeOutFromOne(double duration, Easing easing)
{
    const double startTime = std::max((m_drawable->GetLoadState() == LoadState::Loaded ? m_drawable->GetClock()->GetTime() : 0.), m_nextMinimumStartTime);
    const double endTime = startTime + duration;

    if (startTime < m_minStartTime)
        m_minStartTime = endTime;

    if (endTime > m_maxEndTime)
        m_maxEndTime = endTime;

    m_delay = 0;
    m_nextMinimumStartTime = 0.;

    const auto fadeInTransformation = std::make_shared<Transformation>(m_drawable, TransformationType::Alpha, easing, startTime, startTime, 1.f);
    m_sequence.push_back(fadeInTransformation);

    const auto transformation = std::make_shared<Transformation>(m_drawable, TransformationType::Alpha, easing, startTime, endTime, 0.f);
    m_sequence.push_back(transformation);

    return *this;
}

TransformationSequence& TransformationSequence::MoveTo(Vector2 newPosition, double duration, Easing easing)
{
    const double startTime = std::max((m_drawable->GetLoadState() == LoadState::Loaded ? m_drawable->GetClock()->GetTime() : 0.), m_nextMinimumStartTime);
    const double endTime = startTime + duration;

    if (startTime < m_minStartTime)
        m_minStartTime = endTime;

    if (endTime > m_maxEndTime)
        m_maxEndTime = endTime;

    m_delay = 0;
    m_nextMinimumStartTime = 0.;

    const auto transformation = std::make_shared<Transformation>(m_drawable, TransformationType::Position, easing, startTime, endTime, newPosition);
    m_sequence.push_back(transformation);

    return *this;
}

TransformationSequence& TransformationSequence::MoveToOffset(Vector2 offset, double duration, Easing easing)
{
    const double startTime = std::max((m_drawable->GetLoadState() == LoadState::Loaded ? m_drawable->GetClock()->GetTime() : 0.), m_nextMinimumStartTime);
    const double endTime = startTime + duration;

    if (startTime < m_minStartTime)
        m_minStartTime = endTime;

    if (endTime > m_maxEndTime)
        m_maxEndTime = endTime;

    m_delay = 0;
    m_nextMinimumStartTime = 0.;

    const auto transformation = std::make_shared<Transformation>(m_drawable, TransformationType::PositionOffset, easing, startTime, endTime, offset);
    m_sequence.push_back(transformation);

    return *this;
}

TransformationSequence& TransformationSequence::MoveToX(float newX, double duration, Easing easing)
{
    const double startTime = std::max((m_drawable->GetLoadState() == LoadState::Loaded ? m_drawable->GetClock()->GetTime() : 0.), m_nextMinimumStartTime);
    const double endTime = startTime + duration;

    if (startTime < m_minStartTime)
        m_minStartTime = endTime;

    if (endTime > m_maxEndTime)
        m_maxEndTime = endTime;

    m_delay = 0;
    m_nextMinimumStartTime = 0.;

    const auto transformation = std::make_shared<Transformation>(m_drawable, TransformationType::PositionX, easing, startTime, endTime, newX);
    m_sequence.push_back(transformation);

    return *this;
}

TransformationSequence& TransformationSequence::MoveToY(float newY, double duration, Easing easing)
{
    const double startTime = std::max((m_drawable->GetLoadState() == LoadState::Loaded ? m_drawable->GetClock()->GetTime() : 0.), m_nextMinimumStartTime);
    const double endTime = startTime + duration;

    if (startTime < m_minStartTime)
        m_minStartTime = endTime;

    if (endTime > m_maxEndTime)
        m_maxEndTime = endTime;

    m_delay = 0;
    m_nextMinimumStartTime = 0.;

    const auto transformation = std::make_shared<Transformation>(m_drawable, TransformationType::PositionY, easing, startTime, endTime, newY);
    m_sequence.push_back(transformation);

    return *this;
}

TransformationSequence& TransformationSequence::ResizeTo(Vector2 newSize, double duration, Easing easing)
{
    const double startTime = std::max((m_drawable->GetLoadState() == LoadState::Loaded ? m_drawable->GetClock()->GetTime() : 0.), m_nextMinimumStartTime);
    const double endTime = startTime + duration;

    if (startTime < m_minStartTime)
        m_minStartTime = endTime;

    if (endTime > m_maxEndTime)
        m_maxEndTime = endTime;

    m_delay = 0;
    m_nextMinimumStartTime = 0.;

    const auto transformation = std::make_shared<Transformation>(m_drawable, TransformationType::Size, easing, startTime, endTime, newSize);
    m_sequence.push_back(transformation);

    return *this;
}

TransformationSequence& TransformationSequence::ResizeWidth(float newWidth, double duration, Easing easing)
{
    const double startTime = std::max((m_drawable->GetLoadState() == LoadState::Loaded ? m_drawable->GetClock()->GetTime() : 0.), m_nextMinimumStartTime);
    const double endTime = startTime + duration;

    if (startTime < m_minStartTime)
        m_minStartTime = endTime;

    if (endTime > m_maxEndTime)
        m_maxEndTime = endTime;

    m_delay = 0;
    m_nextMinimumStartTime = 0.;

    const auto transformation = std::make_shared<Transformation>(m_drawable, TransformationType::SizeWidth, easing, startTime, endTime, newWidth);
    m_sequence.push_back(transformation);

    return *this;
}

TransformationSequence& TransformationSequence::ResizeHeight(float newHeight, double duration, Easing easing)
{
    const double startTime = std::max((m_drawable->GetLoadState() == LoadState::Loaded ? m_drawable->GetClock()->GetTime() : 0.), m_nextMinimumStartTime);
    const double endTime = startTime + duration;

    if (startTime < m_minStartTime)
        m_minStartTime = endTime;

    if (endTime > m_maxEndTime)
        m_maxEndTime = endTime;

    m_delay = 0;
    m_nextMinimumStartTime = 0.;

    const auto transformation = std::make_shared<Transformation>(m_drawable, TransformationType::SizeHeight, easing, startTime, endTime, newHeight);
    m_sequence.push_back(transformation);

    return *this;
}

TransformationSequence& TransformationSequence::ScaleTo(Vector2 newScale, double duration, Easing easing)
{
    const double startTime = std::max((m_drawable->GetLoadState() == LoadState::Loaded ? m_drawable->GetClock()->GetTime() : 0.), m_nextMinimumStartTime);
    const double endTime = startTime + duration;

    if (startTime < m_minStartTime)
        m_minStartTime = endTime;

    if (endTime > m_maxEndTime)
        m_maxEndTime = endTime;

    m_delay = 0;
    m_nextMinimumStartTime = 0.;

    const auto transformation = std::make_shared<Transformation>(m_drawable, TransformationType::Scale, easing, startTime, endTime, newScale);
    m_sequence.push_back(transformation);

    return *this;
}

TransformationSequence& TransformationSequence::ScaleTo(float newScale, double duration, Easing easing)
{
    return ScaleTo(Vector2(newScale, newScale), duration, easing);
}

TransformationSequence& TransformationSequence::FadeColor(Color newColor, double duration, Easing easing)
{
    const double startTime = std::max((m_drawable->GetLoadState() == LoadState::Loaded ? m_drawable->GetClock()->GetTime() : 0.), m_nextMinimumStartTime);
    const double endTime = startTime + duration;

    if (startTime < m_minStartTime)
        m_minStartTime = endTime;

    if (endTime > m_maxEndTime)
        m_maxEndTime = endTime;

    m_delay = 0;
    m_nextMinimumStartTime = 0.;

    const auto transformation = std::make_shared<Transformation>(m_drawable, TransformationType::Color, easing, startTime, endTime, newColor);
    m_sequence.push_back(transformation);

    return *this;
}

TransformationSequence& TransformationSequence::FlashColor(Color flashColor, double duration, Easing easing)
{
    const double startTime = std::max((m_drawable->GetLoadState() == LoadState::Loaded ? m_drawable->GetClock()->GetTime() : 0.), m_nextMinimumStartTime);
    const double endTime = startTime + duration;

    if (startTime < m_minStartTime)
        m_minStartTime = endTime;

    if (endTime > m_maxEndTime)
        m_maxEndTime = endTime;

    m_delay = 0;
    m_nextMinimumStartTime = 0.;

    const auto transformation = std::make_shared<Transformation>(m_drawable, TransformationType::FlashColor, easing, startTime, endTime, flashColor);
    m_sequence.push_back(transformation);

    return *this;
}

TransformationSequence& TransformationSequence::Then(double delay)
{
    m_nextMinimumStartTime = m_maxEndTime + m_delay + delay;

    return *this;
}

TransformationSequence& TransformationSequence::Delay(double delay)
{
    m_delay += delay;
    m_nextMinimumStartTime += m_delay;

    return *this;
}

TransformationSequence& TransformationSequence::Loop(double pause)
{
    for (const std::shared_ptr<Transformation>& transformation : m_sequence)
        transformation->Loop(m_maxEndTime - m_minStartTime, pause);

    return *this;
}
