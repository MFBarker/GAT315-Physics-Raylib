#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "gui.h"

#define GUI_DATA(data) TextFormat("%0.2f", data), &data

void GUI::Update()
{
	mouseOverGUI = PhysicsWindowActive && CheckCollisionPointRec(GetMousePosition(), {anchor01.x + 0, anchor01.y + 0, 264, 384});
	if (IsKeyPressed(KEY_TAB)) PhysicsWindowActive = !PhysicsWindowActive;
}

void GUI::Draw()
{
	//Prof Maple did this differently, so I will have to merge things together

	if (select_active) GuiLock();

	if (PhysicsWindowActive)
	{
		PhysicsWindowActive = !GuiWindowBox(Rectangle{ anchor01.x + 0, anchor01.y + 0, 264, 384 }, "PhysicsWindowBox");
		GuiSlider(Rectangle{ anchor01.x + 96, anchor01.y + 48, 120, 16 }, "GRAVITY: ", GUI_DATA(World::gravity.y), -20, 20);
		GuiLabel(Rectangle{ anchor01.x + 8, anchor01.y + 88, 120, 24 }, "BODY CONTROLS:");
		GuiSlider(Rectangle{ anchor01.x + 96, anchor01.y + 168, 120, 16 }, "MASS: ", GUI_DATA(mass), 0.1f, 10);
		GuiSlider(Rectangle{ anchor01.x + 96, anchor01.y + 200, 120, 16 }, "SIZE: ", GUI_DATA(size), 0.02f, 5);
		GuiSlider(Rectangle{ anchor01.x + 96, anchor01.y + 232, 120, 16 }, "G-SCALE: ", GUI_DATA(gravity_scale), 0, 5);
		GuiSlider(Rectangle{ anchor01.x + 96, anchor01.y + 264, 120, 16 }, "DAMPING: ", GUI_DATA(damping), 0, 1);
		GuiSlider(Rectangle{ anchor01.x + 96, anchor01.y + 296, 120, 16 }, "RESTITUTION: ", GUI_DATA(restitution), 0, 1);
		GuiLabel(Rectangle{ anchor01.x + 56, anchor01.y + 120, 120, 24 }, "TYPE:");
		if (GuiDropdownBox(Rectangle{ anchor01.x + 96, anchor01.y + 120, 120, 24 }, "STATIC;KINEMATIC;DYNAMIC", &type, select_active)) select_active = !select_active;
	}

	GuiUnlock();
}

Body* GUI::GetBodyIntersect(const Vector2& position, bodies_t& bodies, const SceneCamera& camera)
{
	for (auto body : bodies)
	{
		if (CheckCollisionPointCircle(position, body->position, body->size)) return body;
	}


	return nullptr;
}
