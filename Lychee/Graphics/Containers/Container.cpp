#include "Container.h"

#include "imgui_internal.h"

void Container::Draw()
{
    Drawable::Draw();

    const bool should_begin_child = !ImGui::GetCurrentContext()->CurrentWindow->IsFallbackWindow;

    if (should_begin_child)
    {
        ImGui::SetNextWindowPos(DrawPosition.ToImVec2());
        ImGui::BeginChild("a", DrawSize.ToImVec2(), false, ImGuiWindowFlags_NoBackground);
    }

    for (Drawable* drawable : m_children)
    {
        drawable->Draw();
    }

    if (should_begin_child)
    {
        ImGui::EndChild();
    }
}

void Container::SetChildren(const std::vector<Drawable*>& children)
{
    for (const Drawable* drawable : m_children)
    {
        delete drawable;
    }

    m_children = children;

    for (Drawable* drawable : m_children)
    {
        drawable->Parent = this;
    }
}

void Container::Add(Drawable* drawable)
{
    drawable->Parent = this;
    m_children.push_back(drawable);
}