#include "Box.h"

void Box::Draw()
{
    Drawable::Draw();

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    drawList->AddRectFilled(GetDrawPosition().ToImVec2(), (GetDrawPosition() + GetDrawSize()).ToImVec2(), Color.ToImGuiHex(GetDrawAlpha()));
}
