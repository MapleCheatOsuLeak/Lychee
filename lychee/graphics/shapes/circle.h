#pragma once

#include "../Drawable.h"

/**
 * \brief A simple circle.
 */
class Circle final : public Drawable
{
public:
	/**
	 * \brief Circle radius. Drawable size is ignored.
	 */
	float Radius = 0.f;

	void Draw() override;
};