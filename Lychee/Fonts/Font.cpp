#include "Font.h"

Font::Font(ImFont* smallFont, ImFont* bigFont)
{
    this->smallFont = smallFont;
    this->bigFont = bigFont;
}

ImFont* Font::ToImGuiFont(int size) const
{
    ImFont* font = size < static_cast<int>(smallFont->FontSize) * 2 ? smallFont : bigFont;
    font->Scale = static_cast<float>(size) / font->FontSize;

    return font;
}
