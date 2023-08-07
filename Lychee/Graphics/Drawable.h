#pragma once

#include "Anchor.h"
#include "Axes.h"
#include "Color.h"
#include "LoadState.h"
#include "Vector2.h"
#include "../DependencyInjection/DependencyContainer.h"
#include "../Input/InputManager.h"
#include "../Timing/Clock.h"
#include "../Transformations/Easing.h"

#include <memory>

class TransformationSequence;

/**
 * \brief Drawables are the basic components in Lychee. Anything that is visible or interactable has to be a drawable.
 */
class Drawable
{
    LoadState m_loadState = LoadState::NotLoaded;
    std::shared_ptr<Clock> m_clock;
    bool m_isCustomClock = false;
    Vector2 m_relativePosition;
    Vector2 m_drawPosition;
    Vector2 m_drawSize;
    Vector2 m_drawScale;
    Color m_drawColor;
    float m_drawAlpha;
    std::vector<std::shared_ptr<TransformationSequence>> m_transformations = {};
    bool m_isHovered = false;

    [[nodiscard]] Vector2 ComputeRelativeAnchorPosition(::Anchor a) const;

protected:
    std::shared_ptr<InputManager> m_inputManager;

    virtual void LateLoad(const std::shared_ptr<DependencyContainer>& dependencyContainer) {}
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
    void Load(const std::shared_ptr<Clock>& defaultClock, const std::shared_ptr<DependencyContainer>& dependencyContainer);
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
    TransformationSequence& FadeIn(double duration = 0., Easing easing = Easing::None);
    TransformationSequence& FadeOut(double duration = 0., Easing easing = Easing::None);
    TransformationSequence& FadeTo(float newAlpha, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& FadeInFromZero(double duration = 0., Easing easing = Easing::None);
    TransformationSequence& FadeOutFromOne(double duration = 0., Easing easing = Easing::None);
    TransformationSequence& MoveTo(Vector2 newPosition, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& MoveToOffset(Vector2 offset, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& MoveToX(float newX, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& MoveToY(float newY, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& ResizeTo(Vector2 newSize, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& ResizeWidth(float newWidth, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& ResizeHeight(float newHeight, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& ScaleTo(Vector2 newScale, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& ScaleTo(float newScale, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& FadeColor(::Color newColor, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& FlashColor(::Color flashColor, double duration = 0., Easing easing = Easing::None);
    TransformationSequence& Delay(double delay);
    /**
     * \return Describes the current state of this Drawable within the loading pipeline.
     */
    LoadState GetLoadState();
    /**
     * \return Clock of this drawable.
     */
    std::shared_ptr<Clock> GetClock();
    /**
     * \brief Sets a custom clock for this drawable.
     * \param newClock New clock to set.
     */
    void SetClock(const std::shared_ptr<Clock>& newClock);
    /**
     * \return Whether or not this drawable is using a custom clock.
     */
    bool GetIsCustomClock();
    /**
     * \brief Updates current time of this drawable's clock.
     * It is recommended to call this method instead of Clock::Update directly.
     * \param deltaTime Time since last frame, in milliseconds.
     */
    virtual void UpdateClock(double deltaTime);
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
     * \return Absolute color of this drawable.
     */
    ::Color GetDrawColor();
    /**
     * \return Absolute alpha factor applied on top of this drawable's color and its existing alpha channel.
     */
    float GetDrawAlpha();
    /**
     * \return Whether this drawable is currently hovered over.
     */
    bool GetIsHovered();
};
