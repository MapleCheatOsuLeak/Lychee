#include "LycheeContext.h"

LycheeContext::LycheeContext()
{
    //ImGui::GetIO().Fonts->AddFontDefault();

    m_dependencyContainer = std::make_shared<DependencyContainer>();
    m_globalClock = std::make_shared<Clock>();
    m_inputManager = std::make_shared<InputManager>();
    m_fontStorage = std::make_shared<FontStorage>();

    m_dependencyContainer->Cache<InputManager>(m_inputManager);
    m_globalClock->Start();
}

std::shared_ptr<FontStorage> LycheeContext::GetFontStorage()
{
    return m_fontStorage;
}

void LycheeContext::Update()
{
    m_inputManager->Update();

    const double deltaTime = static_cast<double>(ImGui::GetIO().DeltaTime) * 1000.;
    m_globalClock->Update(deltaTime);

    for (Drawable* drawable : m_content)
    {
        if (drawable->GetLoadState() != LoadState::Loaded)
            continue;

        if (drawable->GetIsCustomClock())
            drawable->UpdateClock(deltaTime);

        drawable->Update();
    }
}

void LycheeContext::Draw()
{
    for (Drawable* drawable : m_content)
        if (drawable->GetLoadState() == LoadState::Loaded)
            drawable->Draw();
}

void LycheeContext::Add(Drawable* drawable)
{
    if (drawable->GetLoadState() == LoadState::NotLoaded)
        drawable->Load(m_globalClock, m_dependencyContainer);

    m_content.push_back(drawable);
}

void LycheeContext::AddRange(std::initializer_list<Drawable*> drawables)
{
    for (Drawable* drawable : drawables)
        if (drawable->GetLoadState() == LoadState::NotLoaded)
            drawable->Load(m_globalClock, m_dependencyContainer);

    m_content.insert(m_content.end(), drawables);
}