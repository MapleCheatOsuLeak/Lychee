#include "Drawable.h"

Vector2 Drawable::ComputeRelativeAnchorPosition(::Anchor a) const
{
    if (a == Anchor::Custom)
        return CustomAnchorPosition;

    Vector2 result;

    if ((a & Anchor::AX1) != Anchor::None)
        result.X = 0.5f;
    else if ((a & Anchor::AX2) != Anchor::None)
        result.X = 1.f;

    if ((a & Anchor::AY1) != Anchor::None)
        result.Y = 0.5f;
    else if ((a & Anchor::AY2) != Anchor::None)
        result.Y = 1.f;

    return result;
}

void Drawable::Draw()
{
    Alpha = std::clamp(Alpha, 0.f, 1.f);

    const Vector2 parentSize = Parent ? Parent->DrawSize : ImGui::GetIO().DisplaySize;
    const Vector2 parentScale = Parent ? Parent->DrawScale : Vector2(1.f, 1.f);
    const Vector2 parentDrawPosition = Parent ? Parent->DrawPosition : Vector2();
    const float parentAlpha = Parent ? Parent->DrawAlpha : 1.f;

    RelativePosition = parentSize * ComputeRelativeAnchorPosition(Anchor) - DrawSize * ComputeRelativeAnchorPosition(Origin) + Position;

    DrawScale = Scale * parentScale;
    DrawSize = Size * DrawScale;
    DrawAlpha = Alpha * parentAlpha;

    if (RelativeSizeAxes != Axes::None)
    {
        switch (RelativeSizeAxes)
        {
            case Axes::X:
                DrawSize = Vector2(parentSize.X, DrawSize.Y);
                break;
            case Axes::Y:
                DrawSize = Vector2(DrawSize.X, parentSize.Y);
                break;
            case Axes::Both:
                DrawSize = parentSize;
                break;
            case Axes::None:
                break;
        }
    }

    DrawPosition = parentDrawPosition + RelativePosition;
}

void Drawable::UpdateInput(const MouseState& mouseState, const KeyboardState& keyboardState)
{
    // todo: implement input callbacks
}
