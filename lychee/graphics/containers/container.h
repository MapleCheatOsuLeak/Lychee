#pragma once

#include <vector>

#include "../drawable.h"

/**
 * \brief A drawable which can have children added to it.
 * Transformations applied to a container are also applied to its children.
 */
class container : public drawable
{
	std::vector<drawable*> children;
public:
	void draw() override;
	/**
	 * \brief Assigns a new children list to this container.
	 * Calling this method will delete all existing children of this container.
	 * \param children_vec A list of drawables.
	 */
	void set_children(const std::vector<drawable*>& children_vec);
	/**
	 * \brief Adds a new child to this container.
	 * \param drawable Drawable to be added.
	 */
	void add(drawable* drawable);
};