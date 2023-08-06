#include "Circle.h"

void Circle::Update(bool handleInput)
{
    Size = Vector2(Radius * 2, Radius * 2);

    Drawable::Update(handleInput);
}

void Circle::Draw()
{
    Drawable::Draw();

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    drawList->AddCircleFilled((DrawPosition + (DrawSize / Vector2(2.f, 2.f))).ToImVec2(),
                               (RelativeSizeAxes == Axes::X ? DrawSize.X : DrawSize.Y) / 2.f, Color.ToImGuiHex(DrawAlpha));
}
