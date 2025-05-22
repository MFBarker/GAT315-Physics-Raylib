#include "trigonometry_scene.h"


void TrigonometryScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
}

void TrigonometryScene::Update()
{
	
}

void TrigonometryScene::FixedUpdate()
{
}

//trig functions
float DegToRad(float degrees) { return degrees * PI / 180; }
float RadToDeg(float radians) { return radians * 180 /PI; }

float Vector2Length(const Vector2& v) { return sqrtf((v.x * v.x) + (v.y * v.y)); }

//Normalization = vector/max value
Vector2 Vector2normalize(const Vector2& v)
{
	float l = Vector2Length(v);
	if (l == 0) return Vector2{0,0};
	return Vector2{ v.x / l,v.y / l };
	//return (l == 0) ? Vector2{ 0,0 } : Vector2{ v.x / l,v.y / l };
}

void TrigonometryScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, WHITE);
	//DrawCircle(Vector2{ 0, 0 }, 1, RED);
	float radius = 3;
	float rate = 0.8f;
	float time = (float) GetTime() * rate;

	//circle
	int steps = 50;
	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float) steps) * (2 * PI); // 0 - 1
		//float theta = time + ((i / (float) steps) * (2 * PI)); // 0 - 1
		float x = cosf(theta) * radius;
		float y = sinf(theta) * radius;
		DrawCircle(Vector2{ x,y }, 0.2f, RED);
	}

	// sin / cos
	for (float x = -9.0f; x < 9.0f; x += 0.2f)
	{
		float theta = time + ((x / 18.0f) * (2 * PI)); // 0 - 1
		float c = cosf(theta) * radius;
		float s = sinf(theta) * radius;
		DrawCircle(Vector2{ x, c }, 0.2f, GREEN);
		DrawCircle(Vector2{ x, s }, 0.2f, BLUE);
	}

	//orbiting circle
	float theta = time;
	float x = cosf(theta) * radius;
	float y = sinf(theta) * radius;
	DrawCircle(Vector2{ x,y }, 0.2f, YELLOW);

	float angle = atan2f(y, x); //atan (opposite, adjasent) = angle needed [very useful] [atan2 accounts for the 4 quandrants]
	//
	m_camera->EndMode();
}

void TrigonometryScene::DrawGUI()
{
}
