#include "FontStorage.h"

void FontStorage::AddFromFile(const std::string& name, const std::string& filePath)
{
    if (name.empty() && !m_fonts.empty())
        return;

    const ImGuiIO& io = ImGui::GetIO();

    ImFontConfig config;
    config.OversampleH = 2;
    config.OversampleV = 2;

    ImFont* smallFont = io.Fonts->AddFontFromFileTTF(filePath.c_str(), 24, &config);
    ImFont* bigFont = io.Fonts->AddFontFromFileTTF(filePath.c_str(), 72, &config);
    
    m_fonts[name] = std::make_shared<Font>(smallFont, bigFont);
}

void FontStorage::AddFromMemory(const std::string& name, const void* data, int size)
{
    if (name.empty() && !m_fonts.empty())
        return;

    const ImGuiIO& io = ImGui::GetIO();

    // ImGui fonts SUCK!!!
    // So we load two fonts for small and big font sizes, and oversample them to allow for dynamic font resize.
    // This isn't ideal but it works for now. Let's just hope no one overloads font atlast with too many fonts :p
    ImFontConfig config;
    config.OversampleH = 2;
    config.OversampleV = 2;

    ImFont* smallFont = io.Fonts->AddFontFromMemoryCompressedTTF(data, size, 24, &config);
    ImFont* bigFont = io.Fonts->AddFontFromMemoryCompressedTTF(data, size, 72, &config);

    m_fonts[name] = std::make_shared<Font>(smallFont, bigFont);
}

std::shared_ptr<Font> FontStorage::Get(const std::string& name)
{
    std::shared_ptr<Font> result = m_fonts[name];

    return result ? result : m_fonts[{}];
}
