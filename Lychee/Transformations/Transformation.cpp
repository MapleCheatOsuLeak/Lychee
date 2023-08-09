#include "Transformation.h"

double Transformation::interpolate(Easing easing, double time)
{
    switch (easing)
    {
        case Easing::None:
            return time;

        case Easing::In:
        case Easing::InQuad:
            return time * time;

        case Easing::Out:
        case Easing::OutQuad:
            return time * (2. - time);

        case Easing::InOutQuad:
            if (time < .5)
                return time * time * 2.;

            return --time * time * -2. + 1.;

        case Easing::InCubic:
            return time * time * time;

        case Easing::OutCubic:
            return --time * time * time + 1.;

        case Easing::InOutCubic:
            if (time < .5)
                return time * time * time * 4.;

            return --time * time * time * 4. + 1.;

        case Easing::InQuart:
            return time * time * time * time;

        case Easing::OutQuart:
            return 1. - --time * time * time * time;

        case Easing::InOutQuart:
            if (time < .5)
                return time * time * time * time * 8.;

            return --time * time * time * time * -8. + 1.;

        case Easing::InQuint:
            return time * time * time * time * time;

        case Easing::OutQuint:
            return --time * time * time * time * time + 1.;

        case Easing::InOutQuint:
            if (time < .5)
                return time * time * time * time * time * 16.;

            return --time * time * time * time * time * 16. + 1.;

        case Easing::InSine:
            return 1. - std::cos(time * Pi * .5);

        case Easing::OutSine:
            return std::sin(time * Pi * .5);

        case Easing::InOutSine:
            return .5 - .5 * std::cos(Pi * time);

        case Easing::InExpo:
            return std::pow(2., 10. * (time - 1.)) + ExpoOffset * (time - 1.);

        case Easing::OutExpo:
            return -std::pow(2., -10. * time) + 1. + ExpoOffset * time;

        case Easing::InOutExpo:
            if (time < .5)
                return .5 * (std::pow(2., 20. * time - 10.) + ExpoOffset * (2. * time - 1.));

            return 1. - .5 * (std::pow(2., -20. * time + 10.) + ExpoOffset * (-2. * time + 1.));

        case Easing::InCirc:
            return 1. - std::sqrt(1. - time * time);

        case Easing::OutCirc:
            return std::sqrt(1. - --time * time);

        case Easing::InOutCirc:
            if ((time *= 2.) < 1.)
                return .5 - .5 * std::sqrt(1. - time * time);

            return .5 * std::sqrt(1 - (time -= 2.) * time) + .5;

        case Easing::InElastic:
            return -std::pow(2., -10. + 10. * time) * std::sin((1. - ElasticConst2 - time) * ElasticConst) + ElasticOffsetFull * (1. - time);

        case Easing::OutElastic:
            return std::pow(2., -10. * time) * std::sin((time - ElasticConst2) * ElasticConst) + 1. - ElasticOffsetFull * time;

        case Easing::OutElasticHalf:
            return std::pow(2., -10. * time) * std::sin((.5 * time - ElasticConst2) * ElasticConst) + 1. - ElasticOffsetHalf * time;

        case Easing::OutElasticQuarter:
            return std::pow(2., -10. * time) * std::sin((.25 * time - ElasticConst2) * ElasticConst) + 1. - ElasticOffsetQuarter * time;

        case Easing::InOutElastic:
            if ((time *= 2.) < 1.)
                return -.5 * (std::pow(2., -10. + 10. * time) * std::sin((1. - ElasticConst2 * 1.5 - time) * ElasticConst / 1.5) -
                              InOutElasticOffset * (1. - time));

            return .5 * (std::pow(2., -10. * --time) * std::sin((time - ElasticConst2 * 1.5) * ElasticConst / 1.5) - InOutElasticOffset * time) + 1.;

        case Easing::InBack:
            return time * time * ((BackConst + 1.) * time - BackConst);

        case Easing::OutBack:
            return --time * time * ((BackConst + 1.) * time + BackConst) + 1.;

        case Easing::InOutBack:
            if ((time *= 2) < 1)
                return .5 * time * time * ((BackConst2 + 1) * time - BackConst2);

            return .5 * ((time -= 2) * time * ((BackConst2 + 1) * time + BackConst2) + 2);

        case Easing::InBounce:
            time = 1. - time;
            if (time < BounceConst)
                return 1. - 7.5625 * time * time;
            if (time < 2. * BounceConst)
                return 1. - (7.5625 * (time -= 1.5 * BounceConst) * time + .75);
            if (time < 2.5 * BounceConst)
                return 1. - (7.5625 * (time -= 2.25 * BounceConst) * time + .9375);

            return 1 - (7.5625 * (time -= 2.625 * BounceConst) * time + .984375);

        case Easing::OutBounce:
            if (time < BounceConst)
                return 7.5625 * time * time;
            if (time < 2 * BounceConst)
                return 7.5625 * (time -= 1.5 * BounceConst) * time + .75;
            if (time < 2.5 * BounceConst)
                return 7.5625 * (time -= 2.25 * BounceConst) * time + .9375;

            return 7.5625 * (time -= 2.625 * BounceConst) * time + .984375;

        case Easing::InOutBounce:
            if (time < .5)
                return .5 - .5 * interpolate(Easing::OutBounce, 1. - time * 2.);

            return interpolate(Easing::OutBounce, (time - .5) * 2.) * .5 + .5;

        case Easing::OutPow10:
            return --time * std::pow(time, 10.) + 1.;
    }

    return time;
}

Transformation::Transformation(Drawable* drawable, TransformationType type, Easing easing, double startTime, double endTime, float endFloat)
{
    m_drawable = drawable;
    m_type = type;
    m_easing = easing;
    m_startTime = startTime;
    m_endTime = endTime;
    m_endFloat = endFloat;
}

Transformation::Transformation(Drawable* drawable, TransformationType type, Easing easing, double startTime, double endTime, Vector2 endVector)
{
    m_drawable = drawable;
    m_type = type;
    m_easing = easing;
    m_startTime = startTime;
    m_endTime = endTime;
    m_endVector = endVector;
}

Transformation::Transformation(Drawable* drawable, TransformationType type, Easing easing, double startTime, double endTime, Color endColor)
{
    m_drawable = drawable;
    m_type = type;
    m_easing = easing;
    m_startTime = startTime;
    m_endTime = endTime;
    m_endColor = endColor;
}

TransformationType Transformation::GetType()
{
    return m_type;
}

void Transformation::Apply(double time)
{
    if (time < m_startTime)
    {
        m_applied = false;
        m_appliedToEnd = false;

        return;
    }

    // in case we want to rewind a transform that has already been applied to end
    if (time < m_endTime)
        m_appliedToEnd = false;

    if (m_appliedToEnd)
	return;

    const double duration = m_endTime - m_startTime;
    const double remaining = m_endTime - time;
    const auto t = std::max(0.f, std::min(1.f, static_cast<float>(interpolate(m_easing, 1. - remaining / duration))));

    switch (m_type)
    {
        case TransformationType::Alpha:
            if (!m_applied)
                m_startFloat = m_drawable->Alpha;

            m_drawable->Alpha = m_startFloat + t * (m_endFloat - m_startFloat);
            break;
        case TransformationType::Position:
            if (!m_applied)
                m_startVector = m_drawable->Position;

            m_drawable->Position = {m_startVector.X + t * (m_endVector.X - m_startVector.X), m_startVector.Y + t * (m_endVector.Y - m_startVector.Y)};
            break;
        case TransformationType::PositionOffset:
            if (!m_applied)
            {
                m_startVector = m_drawable->Position;
                m_endPositionOffset = m_startVector + m_endVector;
            }

            m_drawable->Position = {m_startVector.X + t * (m_endPositionOffset.X - m_startVector.X), m_startVector.Y + t * (m_endPositionOffset.Y - m_startVector.Y)};
            break;
        case TransformationType::PositionX:
            if (!m_applied)
                m_startFloat = m_drawable->Position.X;

            m_drawable->Position = Vector2(m_startFloat + t * (m_endFloat - m_startFloat), m_drawable->Position.Y);
            break;
        case TransformationType::PositionY:
            if (!m_applied)
                m_startFloat = m_drawable->Position.Y;

            m_drawable->Position = Vector2(m_drawable->Position.X, m_startFloat + t * (m_endFloat - m_startFloat));
            break;
        case TransformationType::Size:
            if (!m_applied)
                m_startVector = m_drawable->Size;

            m_drawable->Size = {m_startVector.X + t * (m_endVector.X - m_startVector.X), m_startVector.Y + t * (m_endVector.Y - m_startVector.Y)};
            break;
        case TransformationType::SizeWidth:
            if (!m_applied)
                m_startFloat = m_drawable->Size.X;

            m_drawable->Size = Vector2(m_startFloat + t * (m_endFloat - m_startFloat), m_drawable->Size.Y);
            break;
        case TransformationType::SizeHeight:
            if (!m_applied)
                m_startFloat = m_drawable->Size.Y;

            m_drawable->Size = Vector2(m_drawable->Size.X, m_startFloat + t * (m_endFloat - m_startFloat));
            break;
        case TransformationType::Scale:
            if (!m_applied)
                m_startVector = m_drawable->Scale;

            m_drawable->Scale = {m_startVector.X + t * (m_endVector.X - m_startVector.X), m_startVector.Y + t * (m_endVector.Y - m_startVector.Y)};
            break;
        case TransformationType::Color:
            if (!m_applied)
                m_startColor = m_drawable->Color;

            m_drawable->Color = {static_cast<uint8_t>(m_startColor.R + t * (m_endColor.R - m_startColor.R)),
                                 static_cast<uint8_t>(m_startColor.G + t * (m_endColor.G - m_startColor.G)),
                                 static_cast<uint8_t>(m_startColor.B + t * (m_endColor.B - m_startColor.B)),
                                 static_cast<uint8_t>(m_startColor.A + t * (m_endColor.A - m_startColor.A))};
            break;
        case TransformationType::FlashColor:
            if (!m_applied)
            {
                m_startColor = m_drawable->Color;
                m_drawable->Color = m_endColor;
                break;
            }

            m_drawable->Color = {static_cast<uint8_t>(m_endColor.R + t * (m_startColor.R - m_endColor.R)),
                                 static_cast<uint8_t>(m_endColor.G + t * (m_startColor.G - m_endColor.G)),
                                 static_cast<uint8_t>(m_endColor.B + t * (m_startColor.B - m_endColor.B)),
                                 static_cast<uint8_t>(m_endColor.A + t * (m_startColor.A - m_endColor.A))};
            break;
    }

    m_applied = true;
    m_appliedToEnd = time >= m_endTime;

    if (m_looped && m_appliedToEnd)
    {
        m_startTime += m_loopOffset + m_loopPause;
        m_endTime = m_startTime + duration;
        m_applied = false;
        m_appliedToEnd = false;
    }
}

void Transformation::Loop(double offset, double pause)
{
    m_looped = true;
    m_loopOffset = offset;
    m_loopPause = pause;
}

void Transformation::Finish()
{
    m_looped = false;

    Apply(m_endTime);
}

bool Transformation::GetIsApplied()
{
    return m_applied;
}

bool Transformation::GetIsAppliedToEnd()
{
    return m_appliedToEnd;
}
