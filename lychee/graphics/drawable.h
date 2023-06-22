#pragma once

#include "anchor.h"
#include "axes.h"
#include "color.h"
#include "vector2.h"

/**
 * \brief Drawables are the basic components in Lychee. Anything that is visible or interactable has to be a drawable.
 */
class drawable
{
	[[nodiscard]] vector2 compute_relative_anchor_position(::anchor a) const;
public:
	/**
	 * \brief The parent of this drawable.
	 */
	drawable* parent = nullptr;

	/**
	 * \brief Positional offset of this drawable's origin in its parent's coordinate system.
	 */
	vector2 position;
	/**
	 * \brief Absolute position of this drawable in its parent's coordinate system. Absolute screen position if parent is null.
	 */
	vector2 draw_position;

	/**
	 * \brief Size of this drawable in its parent's coordinate system.
	 */
	vector2 size;
	/**
	 * \brief Absolute size of this drawable.
	 */
	vector2 draw_size;

	/**
	 * \brief Relative scaling around this drawable's origin.
	 */
	vector2 scale = vector2(1.f, 1.f);
	/**
	 * \brief Absolute scale of this drawable.
	 */
	vector2 draw_scale;

	/**
	 * \brief Color of this drawable.
	 */
	color color;

	/**
	 * \brief Multiplicative alpha factor applied on top of this drawable's color and its existing alpha channel.
	 */
	float alpha = 1.f;
	/**
	 * \brief Absolute alpha factor applied on top of this drawable's color and its existing alpha channel.
	 */
	float draw_alpha = 1.f;

	/**
	 * \brief Specifies where origin of this drawable is attached to the parent.
	 */
	anchor anchor = top_left;
	/**
	 * \brief Specifies where anchor position of this drawable is.
	 */
	vector2 custom_anchor_position;

	/**
	 * \brief The origin of this drawable.
	 */
	::anchor origin = top_left;

	/**
	 * \brief Controls which axes are relatively sized to this drawable's parent size.
	 */
	axes relative_size_axes = axes::none;

    drawable() = default;
    virtual ~drawable() = default;

	/**
	 * \brief Renders this drawable. All low-level (ImGUI) rendering and update logic should be handled in this method.
	 */
	virtual void draw();
};
