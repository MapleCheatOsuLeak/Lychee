#include "Circle.h"

#include "imgui_internal.h"

void Circle::Draw()
{
    Size = Vector2(Radius * 2, Radius * 2);

    Drawable::Draw();

    ImDrawList* drawList = ImGui::GetCurrentContext()->CurrentWindow->IsFallbackWindow ? ImGui::GetBackgroundDrawList() : ImGui::GetWindowDrawList();

    drawList->AddCircleFilled((DrawPosition + (DrawSize / Vector2(2.f, 2.f))).ToImVec2(),
                               (RelativeSizeAxes == Axes::X ? DrawSize.X : DrawSize.Y) / 2.f, Color.ToImGuiHex(DrawAlpha));
}
