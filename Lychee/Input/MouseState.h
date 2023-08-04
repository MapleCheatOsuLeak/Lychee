#pragma once

#include <vector>

#include "MouseButtons.h"
#include "../Graphics/Vector2.h"

class MouseState
{
public:
    Vector2 Position = Vector2();
    Vector2 PreviousPosition = Vector2();
    Vector2 PositionDelta = Vector2();
    std::vector<MouseButtons> PressedButtons = {};
    std::vector<MouseButtons> ReleasedButtons = {};
    float ScrollValue = 0.f;
    float PreviousScrollValue = 0.f;
    float ScrollDelta = 0.f;

    MouseState() = default;
};
