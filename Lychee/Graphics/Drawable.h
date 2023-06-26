#pragma once

#include "Anchor.h"
#include "Axes.h"
#include "Color.h"
#include "Vector2.h"

/**
 * \brief Drawables are the basic components in Lychee. Anything that is visible or interactable has to be a drawable.
 */
class Drawable
{
	[[nodiscard]] Vector2 ComputeRelativeAnchorPosition(::Anchor a) const;
public:
	/**
	 * \brief The parent of this drawable.
	 */
	Drawable* Parent = nullptr;

	/**
	 * \brief Positional offset of this drawable's origin in its parent's coordinate system.
	 */
	Vector2 Position;
	/**
	 * \brief Absolute position of this drawable in its parent's coordinate system. Absolute screen position if parent is null.
	 */
	Vector2 DrawPosition;

	/**
	 * \brief Size of this drawable in its parent's coordinate system.
	 */
	Vector2 Size;
	/**
	 * \brief Absolute size of this drawable.
	 */
	Vector2 DrawSize;

	/**
	 * \brief Relative scaling around this drawable's origin.
	 */
	Vector2 Scale = Vector2(1.f, 1.f);
	/**
	 * \brief Absolute scale of this drawable.
	 */
	Vector2 DrawScale;

	/**
	 * \brief Color of this drawable.
	 */
	Color Color;

	/**
	 * \brief Multiplicative alpha factor applied on top of this drawable's color and its existing alpha channel.
	 */
	float Alpha = 1.f;
	/**
	 * \brief Absolute alpha factor applied on top of this drawable's color and its existing alpha channel.
	 */
	float DrawAlpha = 1.f;

	/**
	 * \brief Specifies where origin of this drawable is attached to the parent.
	 */
	Anchor Anchor = TopLeft;
	/**
	 * \brief Specifies where anchor position of this drawable is.
	 */
	Vector2 CustomAnchorPosition;

	/**
	 * \brief The origin of this drawable.
	 */
	::Anchor Origin = TopLeft;

	/**
	 * \brief Controls which axes are relatively sized to this drawable's parent size.
	 */
	Axes RelativeSizeAxes = Axes::None;

	Drawable() = default;
	virtual ~Drawable() = default;

	/**
	 * \brief Renders this drawable. All low-level (ImGUI) rendering and update logic should be handled in this method.
	 */
	virtual void Draw();
};
