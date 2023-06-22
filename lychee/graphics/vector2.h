#pragma once

#include <cmath>

#include "imgui.h"

struct vector2
{
	float x = 0.f;
	float y = 0.f;

	vector2() = default;

	vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	vector2(ImVec2 im_vec2)
	{
		this->x = im_vec2.x;
		this->y = im_vec2.y;
	}

	[[nodiscard]] ImVec2 to_im_vec2() const
	{
		return {x, y};
	}

	[[nodiscard]] float length() const
	{
		return sqrt(x * x + y * y);
	}

	[[nodiscard]] float length_squared() const
	{
		return x * x + y * y;
	}

	[[nodiscard]] float dot(vector2 v2) const
	{
		return x * v2.x + y * v2.y;
	}

	[[nodiscard]] float distance(vector2 v2) const
	{
		const float dx = x - v2.x;
		const float dy = y - v2.y;

		return sqrtf(dx * dx + dy * dy);
	}

	[[nodiscard]] float distance_squared(vector2 v2) const
	{
		const float dx = x - v2.x;
		const float dy = y - v2.y;

		return dx * dx + dy * dy;
	}

	vector2& operator=(const vector2& v2)
	{
		if (this != &v2)
		{
			x = v2.x;
			y = v2.y;
		}

		return *this;
	}

	vector2 operator+(const vector2& v2) const
	{
		return {x + v2.x, y + v2.y};
	}

	vector2& operator+=(const vector2& v2)
	{
		x += v2.x;
		y += v2.y;

		return *this;
	}

	vector2 operator-(const vector2& v2) const
	{
		return {x - v2.x, y - v2.y};
	}

	vector2& operator-=(const vector2& v2)
	{
		x -= v2.x;
		y -= v2.y;

		return *this;
	}

	vector2 operator*(const vector2& v2) const
	{
		return { x * v2.x, y * v2.y };
	}

	vector2& operator*=(const vector2& v2)
	{
		x *= v2.x;
		y *= v2.y;

		return *this;
	}

	vector2 operator/(const vector2& v2) const
	{
		return { x / v2.x, y / v2.y };
	}

	vector2& operator/=(const vector2& v2)
	{
		x /= v2.x;
		y /= v2.y;

		return *this;
	}

	bool operator==(const vector2& v2) const
	{
		constexpr float epsilon = 0.00001f;

		return std::abs(x - v2.x) < epsilon && std::abs(y - v2.y) < epsilon;
	}

	bool operator!=(const vector2& v2) const
	{
		return !(*this == v2);
	}
};
