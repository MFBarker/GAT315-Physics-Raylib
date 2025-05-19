#include "spring_scene.h"

#include "body.h"
#include "world.h"
#include "raymath.h"
#include "raygui.h"
#include "gui.h"

void SpringScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();

}

void SpringScene::Update()
{
	float dt = GetFrameTime();
	GUI::Update();

	float theta = randomf(0, 360);

	if (IsKeyPressed(KEY_SPACE)) World::simulate = !World::simulate;

	if (!GUI::mouseOverGUI && IsMouseButtonPressed(0)) 
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			Body::Type type = Body::IntToType(GUI::type);

			Body* body = m_world->CreateBody(type, position, GUI::mass, GUI::size, ColorFromHSV(randomf(360), 1, 1));

			body->gravityScale = GUI::gravity_scale;
			body->restitution = GUI::restitution;
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			m_selectedBody = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
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
}

void SpringScene::FixedUpdate()
{
	m_world->Step(fixedTimeStep);
}

void SpringScene::Draw()
{
	m_camera->BeginMode();
	//
	DrawGrid(10, 5, DARKGRAY);

	m_world->Draw(*this);
	if (m_selectedBody)
	{
		//DrawCircleLine(m_world, size, YELLOW);
	}

	//
	m_camera->EndMode();
}

void SpringScene::DrawGUI()
{
	GUI::Draw();
}
