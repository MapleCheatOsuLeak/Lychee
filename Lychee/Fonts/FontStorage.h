#pragma once

#include "Font.h"

#include <string>
#include <unordered_map>

class FontStorage
{
    std::unordered_map<std::string, Font*> fonts;

public:
    FontStorage() = default;
    ~FontStorage();

    void AddFromFile(const std::string& name, std::string filePath);
    void AddFromMemory(const std::string& name, const void* data, int size);
    Font* Get(const std::string& name);
};
