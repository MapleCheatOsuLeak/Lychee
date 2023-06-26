#include "Box.h"

#include "imgui_internal.h"

void Box::Draw()
{
    Drawable::Draw();

    ImDrawList* draw_list = ImGui::GetCurrentContext()->CurrentWindow->IsFallbackWindow ? ImGui::GetBackgroundDrawList() : ImGui::GetWindowDrawList();

    draw_list->AddRectFilled(DrawPosition.ToImVec2(), (DrawPosition + DrawSize).ToImVec2(), Color.ToImGuiHex(DrawAlpha));
}
