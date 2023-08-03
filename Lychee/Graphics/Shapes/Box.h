#pragma once

#include "../drawable.h"

/**
 * \brief A simple rectangular box.
 */
class Box final : public Drawable
{
public:
    void Draw() override;
};