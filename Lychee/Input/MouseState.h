#pragma once

#include <vector>

#include "MouseButtons.h"
#include "../Graphics/Vector2.h"

class MouseState
{
public:
    Vector2 Position = Vector2();
    std::vector<MouseButtons> PressedButtons = {};
    std::vector<MouseButtons> ReleasedButtons = {};
    float ScrollValue = 0;

    MouseState() = default;
};
