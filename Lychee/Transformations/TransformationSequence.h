#pragma once

#include <memory>
#include <vector>

#include "Transformation.h"

class TransformationSequence
{
    std::vector<std::shared_ptr<Transformation>> m_sequence = {};

    std::weak_ptr<Drawable> m_drawable;
    double m_delay = 0.;
    double m_nextMinimumStartTime = 0.;
    double m_minStartTime = 0.;
    double m_maxEndTime = 0.;

public:
    TransformationSequence(const std::shared_ptr<Drawable>& drawable);
    TransformationSequence() = default;

    void ApplyTransformations();
    void FinishTransformations();

    TransformationSequence& FadeIn(double duration = 0., Easing easing = Easing::None);
    TransformationSequence& FadeOut(double duration = 0., Easing easing = Easing::None);
    TransformationSequence& FadeTo(float newAlpha, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& FadeInFromZero(double duration = 0., Easing easing = Easing::None);
    TransformationSequence& FadeOutFromOne(double duration = 0., Easing easing = Easing::None);

    TransformationSequence& MoveTo(Vector2 newPosition, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& MoveToOffset(Vector2 offset, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& MoveToX(float newX, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& MoveToY(float newY, double duration = 0., Easing easing = Easing::None);

    TransformationSequence& ResizeTo(Vector2 newSize, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& ResizeWidth(float newWidth, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& ResizeHeight(float newHeight, double duration = 0., Easing easing = Easing::None);

    TransformationSequence& ScaleTo(Vector2 newScale, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& ScaleTo(float newScale, double duration = 0., Easing easing = Easing::None);

    TransformationSequence& FadeColor(Color newColor, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& FlashColor(Color flashColor, double duration = 0., Easing easing = Easing::None);

    TransformationSequence& Then(double delay = 0.);
    TransformationSequence& Delay(double delay);
    TransformationSequence& Loop(double pause = 0.);
};
