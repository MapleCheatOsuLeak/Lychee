#pragma once

#include "DependencyInjection/DependencyContainer.h"
#include "Fonts/FontStorage.h"
#include "Graphics/Drawable.h"
#include "Input/InputManager.h"

#include <vector>

class LycheeContext
{
    DependencyContainer m_dependencyContainer = DependencyContainer();
    InputManager m_inputManager = InputManager();
    FontStorage m_fontStorage = FontStorage();

    std::vector<Drawable*> m_content = {};
public:
    LycheeContext();

    FontStorage& GetFontStorage();

    void Update();
    void Draw();
    void Add(Drawable* drawable);
    void AddRange(std::initializer_list<Drawable*> drawables);
};