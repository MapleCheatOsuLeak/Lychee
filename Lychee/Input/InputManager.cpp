#include "InputManager.h"

#include "imgui.h"

void InputManager::Update()
{
    const ImGuiIO& io = ImGui::GetIO();

    m_currentMouseState = MouseState();
    m_currentKeyboardState = KeyboardState();

    m_currentMouseState.Position = io.MousePos;

    for (int button = 0; button < 5; button++)
    {
        if (io.MouseDown[button] && !m_previousPressedButtons[button])
            m_currentMouseState.PressedButtons.push_back(static_cast<MouseButtons>(button));
        else if (!io.MouseDown[button] && m_previousPressedButtons[button])
            m_currentMouseState.ReleasedButtons.push_back(static_cast<MouseButtons>(button));
    }

    m_currentMouseState.ScrollValue = io.MouseWheel;

    for (int key = 0; key < 512; key++)
    {
        if (io.KeysDown[key] && !m_previousPressedKeys[key])
            m_currentKeyboardState.PressedKeys.push_back(key);
        else if (!io.KeysDown[key] && m_previousPressedKeys[key])
            m_currentKeyboardState.ReleasedKeys.push_back(key);
    }

    memcpy(m_previousPressedButtons, io.MouseDown, 5);
    memcpy(m_previousPressedKeys, io.KeysDown, 512);
}

bool InputManager::GetShowCursor()
{
    return ImGui::GetIO().MouseDrawCursor;
}

void InputManager::SetShowCursor(bool value)
{
    ImGui::GetIO().MouseDrawCursor = value;
}

MouseState& InputManager::GetMouseState()
{
    return m_currentMouseState;
}

KeyboardState& InputManager::GetKeyboardState()
{
    return m_currentKeyboardState;
}
