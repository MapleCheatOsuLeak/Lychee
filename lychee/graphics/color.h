#pragma once

#include <algorithm>
#include <cstdint>

struct color
{
	uint8_t r = 255;
	uint8_t g = 255;
	uint8_t b = 255;
	uint8_t a = 255;

	color() = default;

	color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	color(unsigned int hex)
	{
		this->r = (hex >> 24) & 0xFF;
		this->g = (hex >> 16) & 0xFF;
		this->b = (hex >> 8) & 0xFF;
		this->a = hex & 0xFF;
	}

	[[nodiscard]] unsigned int to_hex() const
	{
		return ((r & 0xFF) << 24) + ((g & 0xFF) << 16) + ((b & 0xFF) << 8) + (a & 0xFF);
	}

	[[nodiscard]] unsigned int to_hex(float multiplicative_alpha) const
	{
		multiplicative_alpha = std::clamp(multiplicative_alpha, 0.f, 1.f);

		return ((r & 0xFF) << 24) + ((g & 0xFF) << 16) + ((b & 0xFF) << 8) + (static_cast<unsigned char>(multiplicative_alpha * static_cast<float>(a)) & 0xFF);
	}

	[[nodiscard]] unsigned int to_imgui_hex() const
	{
		return r << 0 | g << 8 | b << 16 | a << 24;
	}

	[[nodiscard]] unsigned int to_imgui_hex(float multiplicative_alpha) const
	{
		multiplicative_alpha = std::clamp(multiplicative_alpha, 0.f, 1.f);

		return r << 0 | g << 8 | b << 16 | static_cast<unsigned char>(multiplicative_alpha * static_cast<float>(a)) << 24;
	}
};
