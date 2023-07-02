#include "Container.h"

#include "imgui_internal.h"

void Container::Draw(ImDrawList* drawList)
{
    Drawable::Draw(drawList);

    const bool shouldBeginChild = !ImGui::GetCurrentContext()->CurrentWindow->IsFallbackWindow;

    if (shouldBeginChild)
    {
        ImGui::SetNextWindowPos(DrawPosition.ToImVec2());
        ImGui::BeginChild("a", DrawSize.ToImVec2(), false, ImGuiWindowFlags_NoBackground);
    }
    else
        // no rounded clipping cuz ocornut is gay :')
        drawList->PushClipRect(DrawPosition.ToImVec2(), (DrawPosition + DrawSize).ToImVec2());

    for (Drawable* drawable : m_children)
    {
        drawable->Draw(shouldBeginChild ? ImGui::GetWindowDrawList() : drawList);
    }

    if (shouldBeginChild)
        ImGui::EndChild();
    else
        drawList->PopClipRect();
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