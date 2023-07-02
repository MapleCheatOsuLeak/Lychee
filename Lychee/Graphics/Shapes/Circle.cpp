#include "Circle.h"

void Circle::Draw(ImDrawList* drawList)
{
    Size = Vector2(Radius * 2, Radius * 2);

    Drawable::Draw(drawList);

    drawList->AddCircleFilled((DrawPosition + (DrawSize / Vector2(2.f, 2.f))).ToImVec2(),
                               (RelativeSizeAxes == Axes::X ? DrawSize.X : DrawSize.Y) / 2.f, Color.ToImGuiHex(DrawAlpha));
}
