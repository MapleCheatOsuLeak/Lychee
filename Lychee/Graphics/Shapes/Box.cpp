#include "Box.h"

void Box::Draw()
{
    Drawable::Draw();

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    drawList->AddRectFilled(DrawPosition.ToImVec2(), (DrawPosition + DrawSize).ToImVec2(), Color.ToImGuiHex(DrawAlpha));
}
