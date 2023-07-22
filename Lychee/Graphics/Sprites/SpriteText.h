#pragma once

#include "../Drawable.h"
#include "../../Fonts/Font.h"

#include <string>

class SpriteText : public Drawable
{
public:
    std::string Text;
    Font* Font = nullptr;
    int FontSize = 16;

    void Draw(ImDrawList* drawList) override;
};
