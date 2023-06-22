#include "circle.h"

#include "imgui_internal.h"

void circle::draw()
{
	size = vector2(radius * 2, radius * 2);

	drawable::draw();

	ImDrawList* draw_list = ImGui::GetCurrentContext()->CurrentWindow->IsFallbackWindow ? ImGui::GetBackgroundDrawList() : ImGui::GetWindowDrawList();
	
	draw_list->AddCircleFilled((draw_position + (draw_size / vector2(2.f, 2.f))).to_im_vec2(), (relative_size_axes == axes::x ? draw_size.x : draw_size.y) / 2.f, color.to_imgui_hex(draw_alpha));
}
