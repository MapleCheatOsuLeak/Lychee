#include "SpriteText.h"

void SpriteText::Draw()
{
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    float oldScale = 1.f;
    if (!Font)
    {
        ImFont* defaultFont = ImGui::GetIO().FontDefault ? ImGui::GetIO().FontDefault : ImGui::GetIO().Fonts->Fonts[0];
        oldScale = defaultFont->Scale;
        defaultFont->Scale = static_cast<float>(FontSize) / defaultFont->FontSize;
    }

    ImGui::PushFont(Font ? Font->ToImGuiFont(FontSize) : nullptr);

    Size = ImGui::CalcTextSize(Text.c_str());

    Drawable::Draw();

    ImGui::PopFont();

    if (!Font)
        ImGui::GetFont()->Scale *= GetDrawScale().Y;

    ImGui::PushFont(Font ? Font->ToImGuiFont(static_cast<int>(static_cast<float>(FontSize) * GetDrawScale().Y)) : nullptr);

    drawList->AddText(GetDrawPosition().ToImVec2(), Color.ToImGuiHex(GetDrawAlpha()), Text.c_str());

    if (!Font)
        ImGui::GetFont()->Scale = oldScale;

    ImGui::PopFont();
}
