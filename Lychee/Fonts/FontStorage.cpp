#include "FontStorage.h"

FontStorage::~FontStorage()
{
    for (const auto& font : fonts)
        delete font.second;

    fonts.clear();
}

void FontStorage::AddFromFile(const std::string& name, const std::string& filePath)
{
    const ImGuiIO& io = ImGui::GetIO();

    ImFontConfig config;
    config.OversampleH = 2;
    config.OversampleV = 2;

    ImFont* smallFont = io.Fonts->AddFontFromFileTTF(filePath.c_str(), 24, &config);
    ImFont* bigFont = io.Fonts->AddFontFromFileTTF(filePath.c_str(), 72, &config);
    
    fonts[name] = new Font(smallFont, bigFont);
}

void FontStorage::AddFromMemory(const std::string& name, const void* data, int size)
{
    const ImGuiIO& io = ImGui::GetIO();

    // ImGui fonts SUCK!!!
    // So we load two fonts for small and big font sizes, and oversample them to allow for dynamic font resize.
    // This isn't ideal but it works for now. Let's just hope no one overloads font atlast with too many fonts :p
    ImFontConfig config;
    config.OversampleH = 2;
    config.OversampleV = 2;

    ImFont* smallFont = io.Fonts->AddFontFromMemoryCompressedTTF(data, size, 24, &config);
    ImFont* bigFont = io.Fonts->AddFontFromMemoryCompressedTTF(data, size, 72, &config);

    fonts[name] = new Font(smallFont, bigFont);
}

Font* FontStorage::Get(const std::string& name)
{
    return fonts[name];
}
