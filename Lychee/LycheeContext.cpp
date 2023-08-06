#include "LycheeContext.h"

LycheeContext::LycheeContext()
{
    //ImGui::GetIO().Fonts->AddFontDefault();

    m_dependencyContainer.Cache<InputManager>(&m_inputManager);
}

FontStorage& LycheeContext::GetFontStorage()
{
    return m_fontStorage;
}

void LycheeContext::Update()
{
    m_inputManager.Update();

    for (Drawable* drawable : m_content)
        drawable->Update();
}

void LycheeContext::Draw()
{
    for (Drawable* drawable : m_content)
        drawable->Draw();
}

void LycheeContext::Add(Drawable* drawable)
{
    if (drawable->GetLoadState() == LoadState::NotLoaded)
        drawable->Load(m_dependencyContainer);

    m_content.push_back(drawable);
}

void LycheeContext::AddRange(std::initializer_list<Drawable*> drawables)
{
    for (Drawable* drawable : drawables)
        if (drawable->GetLoadState() == LoadState::NotLoaded)
            drawable->Load(m_dependencyContainer);

    m_content.insert(m_content.end(), drawables);
}