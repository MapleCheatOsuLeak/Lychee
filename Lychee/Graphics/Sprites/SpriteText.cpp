#include "SpriteText.h"

void SpriteText::LateLoad(const std::shared_ptr<DependencyContainer>& dependencyContainer)
{
    m_fontStorage = dependencyContainer->Resolve<FontStorage>();

    m_font = m_fontStorage->Get(m_fontName);
}

void SpriteText::Draw()
{
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    ImGui::PushFont(m_font->ToImGuiFont(FontSize));

    Size = ImGui::CalcTextSize(Text.c_str());

    Drawable::Draw();

    ImGui::PopFont();

    ImGui::PushFont(m_font->ToImGuiFont(static_cast<int>(static_cast<float>(FontSize) * GetDrawScale().Y)));

    drawList->AddText(GetDrawPosition().ToImVec2(), Color.ToImGuiHex(GetDrawAlpha()), Text.c_str());

    ImGui::PopFont();
}

void SpriteText::SetFont(const std::string& fontName)
{
    m_fontName = fontName;

    if (GetLoadState() == LoadState::Loaded)
        m_font = m_fontStorage->Get(m_fontName);
}
