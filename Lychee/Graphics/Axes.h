#pragma once

enum class Axes : unsigned int
{
    None = 0,
    X = 1,
    Y = 1 << 1,
    Both = 1 | (1 << 1)
};

inline Axes operator&(Axes a, Axes b)
{
    return static_cast<Axes>(static_cast<int>(a) & static_cast<int>(b));
}