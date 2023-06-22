#pragma once

#include "../drawable.h"

/**
 * \brief A simple circle.
 */
class circle final : public drawable
{
public:
	/**
	 * \brief Circle radius. Drawable size is ignored.
	 */
	float radius = 0.f;

	void draw() override;
};