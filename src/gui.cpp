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
	if (select_active) GuiLock();

	if (PhysicsWindowActive)
	{
		PhysicsWindowActive = !GuiWindowBox(Rectangle{ anchor01.x + 0, anchor01.y + 0, 312, 464 }, "Physics");
		GuiToggle(Rectangle{ anchor01.x + 24, anchor01.y + 432, 120, 24 }, "Simulate", &World::simulate);
		resetPressed = GuiButton(Rectangle{ anchor01.x + 168, anchor01.y + 432, 120, 24 }, "Reset");
	}

	GuiGroupBox(Rectangle{ anchor02.x + 0, anchor02.y + 0, 264, 176 }, "Body");
	GuiSliderBar(Rectangle{ anchor02.x + 104, anchor02.y + 16, 120, 16 }, "Mass", GUI_DATA(mass), 0, 10);
	GuiSliderBar(Rectangle{ anchor02.x + 104, anchor02.y + 40, 120, 16 }, "Size", GUI_DATA(size), 0.1f, 10.0f);
	GuiSliderBar(Rectangle{ anchor02.x + 104, anchor02.y + 64, 120, 16 }, "Gravity Scale", GUI_DATA(gravity_scale), 0, 10);
	GuiSliderBar(Rectangle{ anchor02.x + 104, anchor02.y + 88, 120, 16 }, "Damping", GUI_DATA(damping), 0, 5);
	GuiSliderBar(Rectangle{ anchor02.x + 104, anchor02.y + 112, 120, 16 }, "Restitution", GUI_DATA(restitution), 0, 2);
	GuiLabel(Rectangle{ anchor02.x + 32, anchor02.y + 136, 120, 24 }, "Body Type");
	GuiGroupBox(Rectangle{ anchor03.x + 0, anchor03.y + 0, 264, 72 }, "Spring");
	GuiSliderBar(Rectangle{ anchor03.x + 104, anchor03.y + 16, 120, 16 }, "Damping", GUI_DATA(springDampingValue), 0, 10);
	GuiSliderBar(Rectangle{ anchor03.x + 104, anchor03.y + 40, 120, 16 }, "Stiffness", GUI_DATA(stiffnessValue), 0, 20);
	GuiGroupBox(Rectangle{ anchor04.x + 0, anchor04.y + -8, 264, 96 }, "World");
	GuiSliderBar(Rectangle{ anchor03.x + 104, anchor03.y + 104, 120, 16 }, "Gravitation", GUI_DATA(World::gravitation), 0, 100);
	GuiSlider(Rectangle{ anchor04.x + 104, anchor04.y + 56, 120, 16 }, "Gravity", GUI_DATA(World::gravity.y), -20, 20);
	GuiSliderBar(Rectangle{ anchor03.x + 104, anchor03.y + 128, 120, 16 }, "Stiffness X", GUI_DATA(World::springStiffnessMultiplier), 0, 100);

	if (GuiDropdownBox(Rectangle{ anchor02.x + 104, anchor02.y + 136, 120, 24 }, "STATIC;KINEMATIC;DYNAMIC", &type, select_active)) select_active = !select_active;

	GuiUnlock();
}

Body* GUI::GetBodyIntersect(const Vector2& position, bodies_t& bodies, const SceneCamera& camera)
{
	for (auto body : bodies)
	{
		if (CheckCollisionPointCircle(position, body->position, body->size))
		{
			return body;
		}
	}

	return nullptr;
}
