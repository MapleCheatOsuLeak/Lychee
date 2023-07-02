#include "Box.h"

void Box::Draw(ImDrawList* drawList)
{
    Drawable::Draw(drawList);

    drawList->AddRectFilled(DrawPosition.ToImVec2(), (DrawPosition + DrawSize).ToImVec2(), Color.ToImGuiHex(DrawAlpha));
}
