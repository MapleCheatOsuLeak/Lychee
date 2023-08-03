#pragma once

#include "Layer.h"
#include "Fonts/FontStorage.h"
#include "Graphics/Drawable.h"

#include <unordered_map>
#include <vector>

class LycheeContext
{
    FontStorage fontStorage = FontStorage();

    std::unordered_map<Layer, std::vector<Drawable*>> layers;
public:
    LycheeContext();

    FontStorage& GetFontStorage();

    void Render();
    void Add(Layer layer, Drawable* drawable);
    void AddRange(Layer layer, std::initializer_list<Drawable*> drawables);
};