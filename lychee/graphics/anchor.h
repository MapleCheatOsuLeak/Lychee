#pragma once

/**
 * \brief Specifies an anchor or origin point from the standard 9 points on a rectangle.
 */
enum Anchor : unsigned int
{
    AY0 = 1,
    AY1 = 1 << 1,
    AY2 = 1 << 2,
    AX0 = 1 << 3,
    AX1 = 1 << 4,
    AX2 = 1 << 5,

    TopLeft = 1 | (1 << 3),
    TopCenter = 1 | (1 << 4),
    TopRight = 1 | (1 << 5),

    CenterLeft = (1 << 1) | (1 << 3),
    Center = (1 << 1) | (1 << 4),
    CenterRight = (1 << 1) | (1 << 5),

    BottomLeft = (1 << 2) | (1 << 3),
    BottomCenter = (1 << 2) | (1 << 4),
    BottomRight = (1 << 2) | (1 << 5),

    Custom = 1 << 6
};