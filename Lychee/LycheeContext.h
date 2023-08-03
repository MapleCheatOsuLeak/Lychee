#pragma once

#include "Fonts/FontStorage.h"
#include "Graphics/Drawable.h"

#include <unordered_map>
#include <vector>

class LycheeContext
{
    FontStorage fontStorage = FontStorage();

    std::vector<Drawable*> m_content = {};
public:
    LycheeContext();

    FontStorage& GetFontStorage();

    void Render();
    void Add(Drawable* drawable);
    void AddRange(std::initializer_list<Drawable*> drawables);
};