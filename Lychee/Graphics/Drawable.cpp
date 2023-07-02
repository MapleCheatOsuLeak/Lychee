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

void Drawable::Draw(ImDrawList* drawList)
{
    Alpha = std::clamp(Alpha, 0.f, 1.f);

    const Vector2 parentSize = Parent ? Parent->DrawSize : ImGui::GetIO().DisplaySize;
    const Vector2 parentScale = Parent ? Parent->DrawScale : Vector2(1.f, 1.f);
    const Vector2 parentPosition = Parent ? Parent->DrawPosition : Vector2();
    const float parentAlpha = Parent ? Parent->DrawAlpha : 1.f;

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

    DrawPosition =
        parentPosition + Position + (parentSize * ComputeRelativeAnchorPosition(Anchor)) - (DrawSize * ComputeRelativeAnchorPosition(Origin));
}
