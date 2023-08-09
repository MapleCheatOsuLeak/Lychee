#pragma once

#include <string>

#include "../Drawable.h"
#include "../../Fonts/Font.h"
#include "../../Fonts/FontStorage.h"

class SpriteText : public Drawable
{
    std::shared_ptr<FontStorage> m_fontStorage;
    std::string m_fontName;
    std::shared_ptr<Font> m_font;

public:
    std::string Text;
    int FontSize = 16;

    void LateLoad(const std::shared_ptr<DependencyContainer>& dependencyContainer) override;
    void Draw() override;

    void SetFont(const std::string& fontName);
};
