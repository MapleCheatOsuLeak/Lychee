#include "LycheeContext.h"

#include "backends/imgui_impl_opengl3.h"
#include "stb_image.h"

#include <stdexcept>

LycheeContext::LycheeContext(Renderer renderer, HWND window)
{
    if (renderer == Renderer::Direct3D9)
        throw std::runtime_error("Direct3D9 not supported."); // todo: add d3d9 support

    m_renderer = renderer;
    m_window = window;

    ImGui::CreateContext();
    ImGui::GetIO().Fonts->AddFontDefault();

    if (renderer == Renderer::OpenGL3)
    {
        // stbi_set_flip_vertically_on_load(0);
        ImGui_ImplOpenGL3_Init();
    }

    ImGui::StyleColorsDark();

    // todo: install input hooks here

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
    if (m_renderer == Renderer::OpenGL3)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
    }

    for (Drawable* drawable : layers[Layer::Background])
        drawable->Draw(ImGui::GetBackgroundDrawList());

    // fallback to background draw list here because the current window draw list is
    // ImGui's debug window and we DO NOT want to push anything to it.
    // Lychee windows will correctly handle draw list stuff in their own rendering routine.
    for (Drawable* drawable : layers[Layer::Foreground])
        drawable->Draw(ImGui::GetBackgroundDrawList());

    for (Drawable* drawable : layers[Layer::Overlay])
        drawable->Draw(ImGui::GetForegroundDrawList());

    if (m_renderer == Renderer::OpenGL3)
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

void LycheeContext::Add(Layer layer, Drawable* drawable)
{
    layers[layer].push_back(drawable);
}

void LycheeContext::AddRange(Layer layer, std::initializer_list<Drawable*> drawables)
{
    layers[layer].insert(layers[layer].end(), drawables);
}