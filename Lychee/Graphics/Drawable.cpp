#include "Drawable.h"

Vector2 Drawable::ComputeRelativeAnchorPosition(::Anchor a) const
{
    if (a == Custom)
        return CustomAnchorPosition;

    Vector2 result;

    if (a & AX1)
        result.X = 0.5f;
    else if (a & AX2)
        result.X = 1.f;

    if (a & AY1)
        result.Y = 0.5f;
    else if (a & AY2)
        result.Y = 1.f;

    return result;
}

void Drawable::Draw()
{
    Alpha = std::clamp(Alpha, 0.f, 1.f);

    const Vector2 ParentSize = Parent ? Parent->DrawSize : ImGui::GetIO().DisplaySize;
    const Vector2 ParentScale = Parent ? Parent->DrawScale : Vector2(1.f, 1.f);
    const Vector2 ParentPosition = Parent ? Parent->DrawPosition : Vector2();
    const float ParentAlpha = Parent ? Parent->DrawAlpha : 1.f;

    DrawScale = Scale * ParentScale;
    DrawSize = Size * DrawScale;
    DrawAlpha = Alpha * ParentAlpha;

    if (RelativeSizeAxes != Axes::None)
    {
        switch (RelativeSizeAxes)
        {
            case Axes::X:
                DrawSize = Vector2(ParentSize.X, DrawSize.Y);
                break;
            case Axes::Y:
                DrawSize = Vector2(DrawSize.X, ParentSize.Y);
                break;
            case Axes::Both:
                DrawSize = ParentSize;
                break;
            case Axes::None:
                break;
        }
    }

    DrawPosition =
        ParentPosition + Position + (ParentSize * ComputeRelativeAnchorPosition(Anchor)) - (DrawSize * ComputeRelativeAnchorPosition(Origin));
}
