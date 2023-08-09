#pragma once

#include "DependencyInjection/DependencyContainer.h"
#include "Fonts/FontStorage.h"
#include "Graphics/Drawable.h"
#include "Input/InputManager.h"

#include <memory>
#include <vector>

class LycheeContext
{
    std::shared_ptr<DependencyContainer> m_dependencyContainer;
    std::shared_ptr<Clock> m_globalClock;
    std::shared_ptr<InputManager> m_inputManager;
    std::shared_ptr<FontStorage> m_fontStorage;

    std::vector<std::shared_ptr<Drawable>> m_content = {};
public:
    LycheeContext();

    std::shared_ptr<FontStorage> GetFontStorage();

    void Update();
    void Draw();
    void Add(const std::shared_ptr<Drawable>& drawable);
    void AddRange(std::initializer_list<std::shared_ptr<Drawable>> drawables);
};