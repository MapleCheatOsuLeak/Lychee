#include "box.h"

#include "imgui_internal.h"

void box::draw()
{
	drawable::draw();

	ImDrawList* draw_list = ImGui::GetCurrentContext()->CurrentWindow->IsFallbackWindow ? ImGui::GetBackgroundDrawList() : ImGui::GetWindowDrawList();

	draw_list->AddRectFilled(draw_position.to_im_vec2(), (draw_position + draw_size).to_im_vec2(), color.to_imgui_hex(draw_alpha));
}
