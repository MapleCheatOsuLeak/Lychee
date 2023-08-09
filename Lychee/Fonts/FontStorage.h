#pragma once

#include "Font.h"

#include <memory>
#include <string>
#include <unordered_map>

class FontStorage
{
    std::unordered_map<std::string, std::shared_ptr<Font>> m_fonts;

public:
    FontStorage() = default;

    void AddFromFile(const std::string& name, const std::string& filePath);
    void AddFromMemory(const std::string& name, const void* data, int size);
    std::shared_ptr<Font> Get(const std::string& name);
};
