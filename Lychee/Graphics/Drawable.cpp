#include "Drawable.h"

#include "../Transformations/TransformationSequence.h"

Vector2 Drawable::ComputeRelativeAnchorPosition(::Anchor a) const
{
    if (a == Anchor::Custom)
        return CustomAnchorPosition;

    Vector2 result;

    if ((a & Anchor::AX1) != Anchor::None)
        result.X = 0.5f;
    else if ((a & Anchor::AX2) != Anchor::None)
        result.X = 1.f;

    if ((a & Anchor::AY1) != Anchor::None)
        result.Y = 0.5f;
    else if ((a & Anchor::AY2) != Anchor::None)
        result.Y = 1.f;

    return result;
}

void Drawable::UpdateInput(const MouseState& mouseState, const KeyboardState& keyboardState)
{
    const bool wasHovered = m_isHovered;

    m_isHovered = mouseState.Position.X > m_drawPosition.X && mouseState.Position.X < m_drawPosition.X + m_drawSize.X &&
                  mouseState.Position.Y > m_drawPosition.Y && mouseState.Position.Y < m_drawPosition.Y + m_drawSize.Y;

    if (m_isHovered)
    {
        for (const MouseButtons& button : mouseState.PressedButtons)
            OnMouseButtonDown(button);

        for (const MouseButtons& button : mouseState.ReleasedButtons)
            OnMouseButtonUp(button);

        if (mouseState.PositionDelta.Length() > 0.f)
            OnMouseMove(mouseState.Position, mouseState.PreviousPosition, mouseState.PositionDelta);

        if (mouseState.ScrollDelta > 0.f)
            OnScroll(mouseState.ScrollValue, mouseState.PreviousScrollValue, mouseState.ScrollDelta);
    }

    if (!wasHovered && m_isHovered)
        OnHover();
    else if (wasHovered && !m_isHovered)
        OnHoverLost();

    for (const int& pressedKey : keyboardState.PressedKeys)
        OnKeyDown(pressedKey);

    for (const int& releasedKey : keyboardState.ReleasedKeys)
        OnKeyUp(releasedKey);
}

void Drawable::UpdateLayout()
{
    Alpha = std::clamp(Alpha, 0.f, 1.f);

    const auto parentSize = Parent ? Parent->m_drawSize : ImGui::GetIO().DisplaySize;
    const auto parentScale = Parent ? Parent->m_drawScale : Vector2(1.f, 1.f);
    const auto parentDrawPosition = Parent ? Parent->m_drawPosition : Vector2();
    const auto parentColor = Parent ? Parent->Color : ::Color();
    const auto parentAlpha = Parent ? Parent->m_drawAlpha : 1.f;

    m_relativePosition = parentSize * ComputeRelativeAnchorPosition(Anchor) - m_drawSize * ComputeRelativeAnchorPosition(Origin) + Position;

    m_drawScale = Scale * parentScale;
    m_drawSize = Size * m_drawScale;
    m_drawColor = Color.Multiply(parentColor);
    m_drawAlpha = Alpha * parentAlpha;

    if (RelativeSizeAxes != Axes::None)
    {
        switch (RelativeSizeAxes)
        {
            case Axes::X:
                m_drawSize = Vector2(parentSize.X, m_drawSize.Y);
                break;
            case Axes::Y:
                m_drawSize = Vector2(m_drawSize.X, parentSize.Y);
                break;
            case Axes::Both:
                m_drawSize = parentSize;
                break;
            case Axes::None:
                break;
        }
    }

    m_drawPosition = parentDrawPosition + m_relativePosition;
}

void Drawable::Load(const std::shared_ptr<Clock>& defaultClock, const std::shared_ptr<DependencyContainer>& dependencyContainer)
{
    if (m_loadState == LoadState::NotLoaded)
    {
        m_loadState = LoadState::Loading;

	if (!m_isCustomClock)
	    m_clock = defaultClock;
        m_inputManager = dependencyContainer->Resolve<InputManager>();
        LateLoad(dependencyContainer);

	m_loadState = LoadState::Loaded;
    }
}

void Drawable::Update(bool handleInput)
{
    if (handleInput)
        UpdateInput(m_inputManager->GetMouseState(), m_inputManager->GetKeyboardState());

    for (const std::shared_ptr<TransformationSequence>& sequence : m_transformations)
        sequence->ApplyTransformations();

    UpdateLayout();
}

TransformationSequence& Drawable::FadeIn(double duration, Easing easing)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->FadeIn(duration, easing);

    return *sequence;
}

TransformationSequence& Drawable::FadeOut(double duration, Easing easing)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->FadeOut(duration, easing);

    return *sequence;
}

TransformationSequence& Drawable::FadeTo(float newAlpha, double duration, Easing easing)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->FadeTo(newAlpha, duration, easing);

    return *sequence;
}

TransformationSequence& Drawable::FadeInFromZero(double duration, Easing easing)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->FadeInFromZero(duration, easing);

    return *sequence;
}

TransformationSequence& Drawable::FadeOutFromOne(double duration, Easing easing)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->FadeOutFromOne(duration, easing);

    return *sequence;
}

TransformationSequence& Drawable::MoveTo(Vector2 newPosition, double duration, Easing easing)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->MoveTo(newPosition, duration, easing);

    return *sequence;
}

TransformationSequence& Drawable::MoveToOffset(Vector2 offset, double duration, Easing easing)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->MoveToOffset(offset, duration, easing);

    return *sequence;
}

TransformationSequence& Drawable::MoveToX(float newX, double duration, Easing easing)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->MoveToX(newX, duration, easing);

    return *sequence;
}

TransformationSequence& Drawable::MoveToY(float newY, double duration, Easing easing)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->MoveToY(newY, duration, easing);

    return *sequence;
}

TransformationSequence& Drawable::ResizeTo(Vector2 newSize, double duration, Easing easing)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->ResizeTo(newSize, duration, easing);

    return *sequence;
}

TransformationSequence& Drawable::ResizeWidth(float newWidth, double duration, Easing easing)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->ResizeWidth(newWidth, duration, easing);

    return *sequence;
}

TransformationSequence& Drawable::ResizeHeight(float newHeight, double duration, Easing easing)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->ResizeHeight(newHeight, duration, easing);

    return *sequence;
}

TransformationSequence& Drawable::ScaleTo(Vector2 newScale, double duration, Easing easing)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->ScaleTo(newScale, duration, easing);

    return *sequence;
}

TransformationSequence& Drawable::ScaleTo(float newScale, double duration, Easing easing)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->ScaleTo(newScale, duration, easing);

    return *sequence;
}

TransformationSequence& Drawable::FadeColor(::Color newColor, double duration, Easing easing)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->FadeColor(newColor, duration, easing);

    return *sequence;
}

TransformationSequence& Drawable::FlashColor(::Color flashColor, double duration, Easing easing)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->FlashColor(flashColor, duration, easing);

    return *sequence;
}

TransformationSequence& Drawable::Delay(double delay)
{
    const auto sequence = std::make_shared<TransformationSequence>(this);
    m_transformations.push_back(sequence);

    sequence->Delay(delay);

    return *sequence;
}

LoadState Drawable::GetLoadState()
{
    return m_loadState;
}

std::shared_ptr<Clock> Drawable::GetClock()
{
    return m_clock;
}

void Drawable::SetClock(const std::shared_ptr<Clock>& newClock)
{
    m_clock = newClock;
    m_isCustomClock = true;
}

bool Drawable::GetIsCustomClock()
{
    return m_isCustomClock;
}

void Drawable::UpdateClock(double deltaTime)
{
    if (!m_isCustomClock)
        return;

    m_clock->Update(deltaTime);
}

Vector2 Drawable::GetRelativePosition()
{
    return m_relativePosition;
}

Vector2 Drawable::GetDrawPosition()
{
    return m_drawPosition;
}

Vector2 Drawable::GetDrawSize()
{
    return m_drawSize;
}

Vector2 Drawable::GetDrawScale()
{
    return m_drawScale;
}

::Color Drawable::GetDrawColor()
{
    return m_drawColor;
}

float Drawable::GetDrawAlpha()
{
    return m_drawAlpha;
}

bool Drawable::GetIsHovered()
{
    return m_isHovered;
}
