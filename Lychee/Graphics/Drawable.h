#pragma once

#include "Anchor.h"
#include "Axes.h"
#include "Color.h"
#include "LoadState.h"
#include "Vector2.h"
#include "../DependencyInjection/DependencyContainer.h"
#include "../Input/InputManager.h"

/**
 * \brief Drawables are the basic components in Lychee. Anything that is visible or interactable has to be a drawable.
 */
class Drawable
{
    LoadState m_loadState = LoadState::NotLoaded;
    Vector2 m_relativePosition;
    Vector2 m_drawPosition;
    Vector2 m_drawSize;
    Vector2 m_drawScale;
    float m_drawAlpha;
    bool m_isHovered = false;

    [[nodiscard]] Vector2 ComputeRelativeAnchorPosition(::Anchor a) const;

protected:
    InputManager* m_inputManager = nullptr;

    virtual void LateLoad(DependencyContainer& dependencyContainer) {}
    void UpdateInput(const MouseState& mouseState, const KeyboardState& keyboardState);
    void UpdateLayout();

public:
    /**
     * \brief The parent of this drawable.
     */
    Drawable* Parent = nullptr;
    /**
     * \brief Positional offset of this drawable's origin in its parent's coordinate system.
     */
    Vector2 Position;
    /**
     * \brief Size of this drawable in its parent's coordinate system.
     */
    Vector2 Size;
    /**
     * \brief Relative scaling around this drawable's origin.
     */
    Vector2 Scale = Vector2(1.f, 1.f);
    /**
     * \brief Color of this drawable.
     */
    Color Color;
    /**
     * \brief Multiplicative alpha factor applied on top of this drawable's color and its existing alpha channel.
     */
    float Alpha = 1.f;
    /**
     * \brief Specifies where origin of this drawable is attached to the parent.
     */
    Anchor Anchor = Anchor::TopLeft;
    /**
     * \brief Specifies where anchor position of this drawable is.
     */
    Vector2 CustomAnchorPosition;
    /**
     * \brief The origin of this drawable.
     */
    ::Anchor Origin = Anchor::TopLeft;
    /**
     * \brief Controls which axes are relatively sized to this drawable's parent size.
     */
    Axes RelativeSizeAxes = Axes::None;

    Drawable() = default;
    virtual ~Drawable() = default;

    /**
     * \brief Loads this drawable, including the gathering of dependencies and initialisation of required resources.
     * \param dependencyContainer Dependency container that will be used to resolve this drawable's dependencies.
     */
    void Load(DependencyContainer& dependencyContainer);
    /**
     * \brief Performs a once-per-frame update specific logic on this drawable.
     * This includes input handling, layout logic and transformation logic.
     * \param handleInput Whether or not input should be handled for this drawable.
     */
    virtual void Update(bool handleInput = true);
    /**
     * \brief Renders this drawable. All low-level (ImGui) rendering logic should be handled in this method.
     */
    virtual void Draw() {}
    virtual void OnMouseButtonDown(MouseButtons button) {}
    virtual void OnMouseButtonUp(MouseButtons button) {}
    virtual void OnMouseMove(Vector2 position, Vector2 previousPosition, Vector2 positionDelta) {}
    virtual void OnScroll(float scrollValue, float previousScrollValue, float scrollDelta) {}
    virtual void OnHover() {}
    virtual void OnHoverLost() {}
    virtual void OnKeyDown(int key) {}
    virtual void OnKeyUp(int key) {}
    /**
     * \return Describes the current state of this Drawable within the loading pipeline.
     */
    enum LoadState GetLoadState();
    /**
     * \return Relative position of this drawable in its parent's coordinate system. Absolute screen position if parent is null.
     */
    Vector2 GetRelativePosition();
    /**
     * \return Absolute screen position of this drawable.
     */
    Vector2 GetDrawPosition();
    /**
     * \return Absolute size of this drawable.
     */
    Vector2 GetDrawSize();
    /**
     * \return Absolute scale of this drawable.
     */
    Vector2 GetDrawScale();
    /**
     * \return Absolute alpha factor applied on top of this drawable's color and its existing alpha channel.
     */
    float GetDrawAlpha();
    /**
     * \return Whether this drawable is currently hovered over.
     */
    bool GetIsHovered();
};
