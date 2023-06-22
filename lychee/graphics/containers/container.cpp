#include "container.h"

#include "imgui_internal.h"

void container::draw()
{
	drawable::draw();

	const bool should_begin_child = !ImGui::GetCurrentContext()->CurrentWindow->IsFallbackWindow;

	if (should_begin_child)
	{
		ImGui::SetNextWindowPos(draw_position.to_im_vec2());
		ImGui::BeginChild("a", draw_size.to_im_vec2(), false, ImGuiWindowFlags_NoBackground);
	}

	for (drawable* drawable : children)
		drawable->draw();

	if (should_begin_child)
		ImGui::EndChild();
}

void container::set_children(const std::vector<drawable*>& children_vec)
{
	for (const drawable* drawable : children)
		delete drawable;

	children = children_vec;

	for (drawable* drawable : children)
		drawable->parent = this;
}

void container::add(drawable* drawable)
{
	drawable->parent = this;
	children.push_back(drawable);
}
