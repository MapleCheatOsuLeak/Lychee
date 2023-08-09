#include "InputManager.h"

#include "imgui.h"

InputManager::InputManager()
{
    const ImGuiIO& io = ImGui::GetIO();

    m_previousMousePosition = io.MousePos;
    m_previousScrollValue = io.MouseWheel;
    memcpy(m_previousPressedButtons, io.MouseDown, 5);

    memcpy(m_previousPressedKeys, io.KeysDown, 512);
}

void InputManager::Update()
{
    const ImGuiIO& io = ImGui::GetIO();

    m_currentMouseState = MouseState();
    m_currentKeyboardState = KeyboardState();

    m_currentMouseState.Position = io.MousePos;
    m_currentMouseState.PreviousPosition = m_previousMousePosition;
    m_currentMouseState.PositionDelta = m_currentMouseState.Position - m_currentMouseState.PreviousPosition;

    for (int button = 0; button < 5; button++)
    {
        if (io.MouseDown[button] && !m_previousPressedButtons[button])
            m_currentMouseState.PressedButtons.push_back(static_cast<MouseButtons>(button));
        else if (!io.MouseDown[button] && m_previousPressedButtons[button])
            m_currentMouseState.ReleasedButtons.push_back(static_cast<MouseButtons>(button));
    }

    m_currentMouseState.ScrollValue = io.MouseWheel;
    m_currentMouseState.PreviousScrollValue = m_previousScrollValue;
    m_currentMouseState.ScrollDelta = io.MouseWheel - m_previousScrollValue;

    for (int key = 0; key < 512; key++)
    {
        if (io.KeysDown[key] && !m_previousPressedKeys[key])
            m_currentKeyboardState.PressedKeys.push_back(key);
        else if (!io.KeysDown[key] && m_previousPressedKeys[key])
            m_currentKeyboardState.ReleasedKeys.push_back(key);
    }

    m_previousMousePosition = io.MousePos;
    m_previousScrollValue = io.MouseWheel;
    std::copy_n(io.MouseDown, 5, m_previousPressedButtons);

    std::copy_n(io.KeysDown, 512, m_previousPressedKeys);
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
