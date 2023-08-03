#include "LycheeContext.h"

LycheeContext::LycheeContext()
{
    ImGui::GetIO().Fonts->AddFontDefault();
}

FontStorage& LycheeContext::GetFontStorage()
{
    return fontStorage;
}

void LycheeContext::Render()
{
    for (Drawable* drawable : m_content)
        drawable->Draw();
}

void LycheeContext::Add(Drawable* drawable)
{
    m_content.push_back(drawable);
}

void LycheeContext::AddRange(std::initializer_list<Drawable*> drawables)
{
    m_content.insert(m_content.end(), drawables);
}