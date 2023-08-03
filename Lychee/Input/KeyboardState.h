#pragma once

#include <vector>

class KeyboardState
{
public:
    std::vector<int> PressedKeys = {};
    std::vector<int> ReleasedKeys = {};

    KeyboardState() = default;
};
