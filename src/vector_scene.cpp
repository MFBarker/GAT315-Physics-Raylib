#include "vector_scene.h"
#include "body.h"
#include "gravitation.h"
#include "world.h"
#include "raymath.h"
#include "raygui.h"

#define GUI_DATA(data) TextFormat("%0.2f", data), &data

void VectorScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();

}

void VectorScene::Update()
{
	float dt = GetFrameTime();

	float theta = randomf(0, 360);

	if (IsMouseButtonPressed(0)) 
	{
		int pattern = 0;

		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());

		for (int i = 0; i < 100; i++)
		{
			float angle = 0.0f;
			float speed = randomf(2, 6);

			switch (pattern)
			{
			case 0: // Circular explosion
				angle = randomf(0, 360);
				break;

			case 1: // Directional burst
				angle = theta * theta;
				break;

			case 2: // Spiral
				angle = i * 7;
				speed = 0.05f * i + 1.0f;
				break;
			}

			float x = cosf(angle);
			float y = sinf(angle);
			Vector2 velocity = Vector2{ x, y } * speed;

			Body* body = m_world->CreateBody(position, size, ColorFromHSV(randomf(360), 1, 1));
			body->velocity = velocity;
			body->gravityScale = gravity_scale;

			body->restitution = restitution;
		}
	}
	//apply forces
	
	//applycollision
	for (auto body : m_world->GetBodies())
	{
		if (body->position.y < -5)
		{
			body->position.y = -5;
			body->velocity.y *= -body->restitution;
		}
		if (body->position.x < -9)
		{
			body->position.x = -9;
			body->velocity.x *= -body->restitution;
		}
		if (body->position.x > 9)
		{
			body->position.x = 9;
			body->velocity.x *= -body->restitution;
		}
	}
	m_world->UpdateBodies(mass,size,damping,gravity_scale,type);
}

void VectorScene::FixedUpdate()
{
	ApplyGravitation(m_world->GetBodies(), 0.15f);

	m_world->Step(fixedTimeStep);
}

void VectorScene::Draw()
{
	m_camera->BeginMode();
	//
	DrawGrid(10, 5, DARKGRAY);

	m_world->Draw(*this);

	//
	m_camera->EndMode();
}

void VectorScene::DrawGUI()
{
	//Prof Maple did this differently, so I will have to merge things together
	if (select_active) GuiLock();

	if (PhysicsWindowActive)
	{
		PhysicsWindowActive = !GuiWindowBox( Rectangle{ anchor01.x + 0, anchor01.y + 0, 264, 384 }, "PhysicsWindowBox");
		GuiSlider(Rectangle{ anchor01.x + 96, anchor01.y + 48, 120, 16 }, "GRAVITY: ", GUI_DATA(World::gravity.y), -20, 20);
		GuiLabel( Rectangle{ anchor01.x + 8, anchor01.y + 88, 120, 24 }, "BODY CONTROLS:");
		GuiSlider(Rectangle{ anchor01.x + 96, anchor01.y + 168, 120, 16 }, "MASS: ", GUI_DATA(mass), 0.1f, 10);
		GuiSlider( Rectangle{ anchor01.x + 96, anchor01.y + 200, 120, 16 }, "SIZE: ", GUI_DATA(size), 0.02f, 5);
		GuiSlider(Rectangle{ anchor01.x + 96, anchor01.y + 232, 120, 16 }, "G-SCALE: ", GUI_DATA(gravity_scale), 0, 5);
		GuiSlider( Rectangle{ anchor01.x + 96, anchor01.y + 264, 120, 16 }, "DAMPING: ", GUI_DATA(damping), 0, 1);
		GuiSlider( Rectangle{ anchor01.x + 96, anchor01.y + 296, 120, 16 }, "RESTITUTION: ", GUI_DATA(restitution), 0, 1);
		GuiLabel( Rectangle{ anchor01.x + 56, anchor01.y + 120, 120, 24 }, "TYPE:");
		if (GuiDropdownBox( Rectangle{ anchor01.x + 96, anchor01.y + 120, 120, 24 }, "STATIC;KINEMATIC;DYNAMIC", & type, select_active)) select_active = !select_active;
	}

	GuiUnlock();
}
