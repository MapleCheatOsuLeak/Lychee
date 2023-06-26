#pragma once

#include <algorithm>
#include <cstdint>

struct Color
{
	uint8_t R = 255;
	uint8_t G = 255;
	uint8_t B = 255;
	uint8_t A = 255;

	Color() = default;

	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		R = r;
		G = g;
		B = b;
		A = a;
	}

	Color(unsigned int hex)
	{
		R = (hex >> 24) & 0xFF;
		G = (hex >> 16) & 0xFF;
		B = (hex >> 8) & 0xFF;
		A = hex & 0xFF;
	}

	[[nodiscard]] unsigned int ToHex() const
	{
		return ((R & 0xFF) << 24) + ((G & 0xFF) << 16) + ((B & 0xFF) << 8) + (A & 0xFF);
	}

	[[nodiscard]] unsigned int ToHex(float alpha) const
	{
		alpha = std::clamp(alpha, 0.f, 1.f);

		return ((R & 0xFF) << 24) + ((G & 0xFF) << 16) + ((B & 0xFF) << 8) + (static_cast<unsigned char>(alpha * static_cast<float>(A)) & 0xFF);
	}

	[[nodiscard]] unsigned int ToImGuiHex() const
	{
		return R << 0 | G << 8 | B << 16 | A << 24;
	}

	[[nodiscard]] unsigned int ToImGuiHex(float alpha) const
	{
		alpha = std::clamp(alpha, 0.f, 1.f);

		return R << 0 | G << 8 | B << 16 | static_cast<unsigned char>(alpha * static_cast<float>(A)) << 24;
	}
};
