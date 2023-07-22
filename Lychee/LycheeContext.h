#pragma once

#include "Layer.h"
#include "Renderer.h"
#include "Fonts/FontStorage.h"
#include "Graphics/Drawable.h"

#include <unordered_map>
#include <vector>
#include <wtypes.h>

class LycheeContext
{
    Renderer renderer;
    HWND window;

    FontStorage fontStorage = FontStorage();

    std::unordered_map<Layer, std::vector<Drawable*>> layers;
public:
    LycheeContext(Renderer renderer, HWND window);

    FontStorage* GetFontStorage();

    void Render();
    void Add(Layer layer, Drawable* drawable);
    void AddRange(Layer layer, std::initializer_list<Drawable*> drawables);
};