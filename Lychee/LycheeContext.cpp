#include "LycheeContext.h"

LycheeContext::LycheeContext()
{
    ImGui::GetIO().Fonts->AddFontDefault();

    layers[Layer::Background] = {};
    layers[Layer::Foreground] = {};
    layers[Layer::Overlay] = {};
}

FontStorage& LycheeContext::GetFontStorage()
{
    return fontStorage;
}

void LycheeContext::Render()
{
    for (Drawable* drawable : layers[Layer::Background])
        drawable->Draw(ImGui::GetBackgroundDrawList());

    // fallback to background draw list here because the current window draw list is
    // ImGui's debug window and we DO NOT want to push anything to it.
    // Lychee windows will correctly handle draw list stuff in their own rendering routine.
    for (Drawable* drawable : layers[Layer::Foreground])
        drawable->Draw(ImGui::GetBackgroundDrawList());

    for (Drawable* drawable : layers[Layer::Overlay])
        drawable->Draw(ImGui::GetForegroundDrawList());
}

void LycheeContext::Add(Layer layer, Drawable* drawable)
{
    layers[layer].push_back(drawable);
}

void LycheeContext::AddRange(Layer layer, std::initializer_list<Drawable*> drawables)
{
    layers[layer].insert(layers[layer].end(), drawables);
}