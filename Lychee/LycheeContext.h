#pragma once

#include "Layer.h"
#include "Renderer.h"
#include "Graphics/Drawable.h"

#include <unordered_map>
#include <vector>
#include <wtypes.h>

class LycheeContext
{
    Renderer renderer;
    HWND window;

    std::unordered_map<Layer, std::vector<Drawable*>> layers;
public:
    LycheeContext(Renderer renderer, HWND window);

    void Render();
    void Add(Layer layer, Drawable* drawable);
    void AddRange(Layer layer, std::initializer_list<Drawable*> drawables);
};