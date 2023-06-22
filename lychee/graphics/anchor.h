#pragma once

/**
 * \brief Specifies an anchor or origin point from the standard 9 points on a rectangle.
 */
enum anchor : unsigned int
{
    ay0 = 1,
    ay1 = 1 << 1,
    ay2 = 1 << 2,
    ax0 = 1 << 3,
    ax1 = 1 << 4,
    ax2 = 1 << 5,

    top_left = 1 | (1 << 3),
    top_center = 1 | (1 << 4),
    top_right = 1 | (1 << 5),

    center_left = (1 << 1) | (1 << 3),
    center = (1 << 1) | (1 << 4),
    center_right = (1 << 1) | (1 << 5),

    bottom_left = (1 << 2) | (1 << 3),
    bottom_center = (1 << 2) | (1 << 4),
    bottom_right = (1 << 2) | (1 << 5),

    custom = 1 << 6
};