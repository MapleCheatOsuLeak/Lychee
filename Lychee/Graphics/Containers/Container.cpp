#include "Container.h"

#include <stdexcept>

void Container::LateLoad(DependencyContainer& dependencyContainer)
{
    m_dependencyContainer = dependencyContainer;

    for (Drawable* drawable : m_children)
        drawable->Load(dependencyContainer);
}

void Container::Update(bool handleInput)
{
    if (AutoSizeAxes != Axes::None)
    {
        if ((RelativeSizeAxes & AutoSizeAxes) != Axes::None)
            throw std::runtime_error("No axis can be relatively sized and automatically sized at the same time.");

        Vector2 maxSize;
        for (const Drawable* child : m_children)
        {
            if ((child->RelativeSizeAxes & Axes::X) == Axes::None)
                maxSize.X = std::max(child->DrawSize.X, maxSize.X);

            if ((child->RelativeSizeAxes & Axes::Y) == Axes::None)
                maxSize.Y = std::max(child->DrawSize.Y, maxSize.Y);
        }

        switch (AutoSizeAxes)
        {
            case Axes::X:
                Size = Vector2(maxSize.X, Size.Y);
                Scale = Vector2(1.f, Scale.Y);
                break;
            case Axes::Y:
                Size = Vector2(Size.X, maxSize.Y);
                Scale = Vector2(Scale.X, 1.f);
                break;
            case Axes::Both:
                Size = maxSize;
                Scale = Vector2(1.f, 1.f);
                break;
            case Axes::None:
                break;
        }
    }

    Drawable::Update();

    for (Drawable* drawable : m_children)
        drawable->Update(handleInput && PassThroughInput);
}

void Container::Draw()
{
    Drawable::Draw();

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    drawList->PushClipRect(DrawPosition.ToImVec2(), (DrawPosition + DrawSize).ToImVec2());

    for (Drawable* drawable : m_children)
        drawable->Draw();

    drawList->PopClipRect();
}

void Container::SetChildren(const std::vector<Drawable*>& children)
{
    for (const Drawable* drawable : m_children)
        delete drawable;

    m_children = children;

    for (Drawable* drawable : m_children)
    {
        drawable->Parent = this;

        if (LoadState == ::LoadState::Ready)
            drawable->Load(m_dependencyContainer);
    }
}

void Container::Add(Drawable* drawable)
{
    drawable->Parent = this;

    if (LoadState == ::LoadState::Ready)
        drawable->Load(m_dependencyContainer);

    m_children.push_back(drawable);
}