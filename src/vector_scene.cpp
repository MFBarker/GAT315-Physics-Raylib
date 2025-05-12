#include "vector_scene.h"
#include "body.h"
#include "raymath.h"
#include "math_utils.h"

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

	if (IsMouseButtonDown(0)) 
	{
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
		for (int i = 0;i < 100; i++)
		{
			Body* body = m_world->CreateBody(position, 0.2f, ColorFromHSV(randomf(360),1,1));
			float offset = randomf(0, 360);
			float x = cos(theta);
			float y = sin(theta);
			body->velocity = Vector2{ x,y } * randomf(1,6);
			body->gravityScale = 0.2f;
		}
	}
	//apply forces
	m_world->Step(dt);
	//applycollision
	for (auto body : m_world->GetBodies())
	{
		if (body->position.y < -5)
		{
			body->position.y = -5;
			body->velocity.y *= -1;
		}

		//honk
	}
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
}
