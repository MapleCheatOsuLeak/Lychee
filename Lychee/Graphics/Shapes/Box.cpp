#include "Box.h"

void Box::Draw()
{
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    drawList->AddRectFilled(GetDrawPosition().ToImVec2(), (GetDrawPosition() + GetDrawSize()).ToImVec2(), GetDrawColor().ToImGuiHex(GetDrawAlpha()));
}
