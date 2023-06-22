#include "drawable.h"

vector2 drawable::compute_relative_anchor_position(::anchor a) const
{
	if (a == custom)
		return custom_anchor_position;

	vector2 result;
	
	if (a & ax1)
		result.x = 0.5f;
	else if (a & ax2)
		result.x = 1.f;

	if (a & ay1)
		result.y = 0.5f;
	else if (a & ay2)
		result.y = 1.f;

	return result;
}

void drawable::draw()
{
	alpha = std::clamp(alpha, 0.f, 1.f);

	const vector2 parent_size = parent ? parent->draw_size : ImGui::GetIO().DisplaySize;
	const vector2 parent_scale = parent ? parent->draw_scale : vector2(1.f, 1.f);
	const vector2 parent_position = parent ? parent->draw_position : vector2();
	const float parent_alpha = parent ? parent->draw_alpha : 1.f;

	draw_scale = scale * parent_scale;
	draw_size = size * draw_scale;
	draw_alpha = alpha * parent_alpha;

	if (relative_size_axes != axes::none)
	{
		switch (relative_size_axes)
		{
			case axes::x:
				draw_size = vector2(parent_size.x, draw_size.y);
				break;
			case axes::y:
				draw_size = vector2(draw_size.x, parent_size.y);
				break;
			case axes::both:
				draw_size = parent_size;
				break;
			case axes::none:
				break;
		}
	}
	
	draw_position = parent_position + position + (parent_size * compute_relative_anchor_position(anchor)) - (draw_size * compute_relative_anchor_position(origin));
}
