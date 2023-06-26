#include "Box.h"

#include "imgui_internal.h"

void Box::Draw()
{
    Drawable::Draw();

    ImDrawList* drawList = ImGui::GetCurrentContext()->CurrentWindow->IsFallbackWindow ? ImGui::GetBackgroundDrawList() : ImGui::GetWindowDrawList();

    drawList->AddRectFilled(DrawPosition.ToImVec2(), (DrawPosition + DrawSize).ToImVec2(), Color.ToImGuiHex(DrawAlpha));
}
