#pragma once

#include "KeyboardState.h"
#include "MouseState.h"

class InputManager
{
    Vector2 m_previousMousePosition = Vector2();
    float m_previousScrollValue = 0;
    bool m_previousPressedButtons[5];
    bool m_previousPressedKeys[512];

    MouseState m_currentMouseState = MouseState();
    KeyboardState m_currentKeyboardState = KeyboardState();

public:
    InputManager();

    void Update();
    bool GetShowCursor();
    void SetShowCursor(bool value);
    MouseState& GetMouseState();
    KeyboardState& GetKeyboardState();
};
