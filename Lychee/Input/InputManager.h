#pragma once

#include "KeyboardState.h"
#include "MouseState.h"

class InputManager
{
    bool m_previousPressedButtons[5];
    bool m_previousPressedKeys[512];

    MouseState m_currentMouseState = MouseState();
    KeyboardState m_currentKeyboardState = KeyboardState();

public:
    InputManager() = default;

    void Update();
    bool GetShowCursor();
    void SetShowCursor(bool value);
    MouseState& GetMouseState();
    KeyboardState& GetKeyboardState();
};
