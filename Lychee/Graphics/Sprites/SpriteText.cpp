#include "SpriteText.h"

void SpriteText::Draw(ImDrawList* drawList)
{
    float oldScale = 1.f;
    if (!Font)
    {
        ImFont* defaultFont = ImGui::GetIO().FontDefault ? ImGui::GetIO().FontDefault : ImGui::GetIO().Fonts->Fonts[0];
        oldScale = defaultFont->Scale;
        defaultFont->Scale = static_cast<float>(FontSize) / defaultFont->FontSize;
    }

    ImGui::PushFont(Font ? Font->ToImGuiFont(FontSize) : nullptr);

    Size = ImGui::CalcTextSize(Text.c_str());

    Drawable::Draw(drawList);

    ImGui::PopFont();

    if (!Font)
        ImGui::GetFont()->Scale *= DrawScale.Y;

    ImGui::PushFont(Font ? Font->ToImGuiFont(static_cast<int>(static_cast<float>(FontSize) * DrawScale.Y)) : nullptr);

    drawList->AddText(DrawPosition.ToImVec2(), Color.ToImGuiHex(DrawAlpha), Text.c_str());

    if (!Font)
        ImGui::GetFont()->Scale = oldScale;

    ImGui::PopFont();
}
