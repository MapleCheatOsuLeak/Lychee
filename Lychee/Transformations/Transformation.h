#pragma once

#include "../Graphics/Color.h"
#include "../Graphics/Vector2.h"
#include "Easing.h"
#include "TransformationType.h"
#include "../Graphics/Drawable.h"

class Transformation
{
    static inline double Pi = 3.14159265358979323846;
    static inline double ElasticConst = 2. * Pi / .3;
    static inline double ElasticConst2 = .3 / 4;
    static inline double BackConst = 1.70158;
    static inline double BackConst2 = BackConst * 1.525;
    static inline double BounceConst = 1. / 2.75;
    static inline double ExpoOffset = std::pow(2., -10.);
    static inline double ElasticOffsetFull = std::pow(2., -11.);
    static inline double ElasticOffsetHalf = std::pow(2., -10.) * std::sin((.5 - ElasticConst2) * ElasticConst);
    static inline double ElasticOffsetQuarter = std::pow(2., -10.) * std::sin((.25 - ElasticConst2) * ElasticConst);
    static inline double InOutElasticOffset = std::pow(2., -10.) * std::sin((1. - ElasticConst2 * 1.5) * ElasticConst / 1.5);

    static double interpolate(Easing easing, double time);

    std::weak_ptr<Drawable> m_drawable;
    TransformationType m_type = TransformationType::Alpha;
    Easing m_easing = Easing::None;
    double m_startTime = 0.;
    double m_endTime = 0.;
    bool m_applied = false;
    bool m_appliedToEnd = false;
    bool m_looped = false;
    double m_loopOffset = 0.;
    double m_loopPause = 0.;
    float m_startFloat = 0.f;
    float m_endFloat = 0.f;
    Vector2 m_startVector = Vector2();
    Vector2 m_endVector = Vector2();
    Vector2 m_endPositionOffset = Vector2();
    Color m_startColor = Color();
    Color m_endColor = Color();

public:
    Transformation(const std::shared_ptr<Drawable>& drawable, TransformationType type, Easing easing, double startTime, double endTime, float endFloat);
    Transformation(const std::shared_ptr<Drawable>& drawable, TransformationType type, Easing easing, double startTime, double endTime, Vector2 endVector);
    Transformation(const std::shared_ptr<Drawable>& drawable, TransformationType type, Easing easing, double startTime, double endTime, Color endColor);
    Transformation() = default;

    TransformationType GetType();
    void Apply(double time);
    void Loop(double offset, double pause);
    void Finish();
    bool GetIsApplied();
    bool GetIsAppliedToEnd();
};
