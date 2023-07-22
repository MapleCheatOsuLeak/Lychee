#pragma once

#include "imgui.h"

class Font
{
    ImFont* smallFont = nullptr;
    ImFont* bigFont = nullptr;

public:
    Font(ImFont* smallFont, ImFont* bigFont);

    ImFont* ToImGuiFont(int size) const;
};
