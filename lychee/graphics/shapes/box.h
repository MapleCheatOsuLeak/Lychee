#pragma once

#include "../drawable.h"

/**
 * \brief A simple rectangular box.
 */
class box final : public drawable
{
	void draw() override;
};