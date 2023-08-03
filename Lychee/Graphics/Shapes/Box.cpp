#include "Box.h"

void Box::Draw()
{
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    Drawable::Draw();

    drawList->AddRectFilled(DrawPosition.ToImVec2(), (DrawPosition + DrawSize).ToImVec2(), Color.ToImGuiHex(DrawAlpha));
}
