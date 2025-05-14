#include "polar_scene.h"

//#define ARCHIMEDIAN
//#define CARDIOID
//#define LIMACON
//#define ROSE
#define USER

void PolarScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
}

void PolarScene::Update()
{
}

void PolarScene::FixedUpdate()
{
}

void PolarScene::Draw()
{
	m_camera->BeginMode();

#ifdef ARCHIMEDIAN
	//r = a + (b * theta)
	int steps = 200;
	float time = (float)GetTime();
	float a = 0;
	float b = 0.35f;
	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float)steps) * (8 * PI);
		float r = a + (b * theta);

		Polar p{ time + theta, r };
		DrawCircle(p, 0.2f, GREEN);
	}
#elif defined CARDIOID
	//r = a( 1 + cos(theta) )
	int steps = 200;
	float time = (float)GetTime();
	float scaling = 0.15f;
	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float)steps) * (8 * PI);
		float a = scaling * theta;
		float r = a * ( 1 + cos(theta) );

		Polar p{ time + theta, r };
		DrawCircle(p, 0.2f, RED);
	}

#elif defined LIMACON
	//r = a + ( b * cos(theta) )
	int steps = 200;
	float time = (float)GetTime();
	float a = 2.0f;
	float b = 4.0f;

	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float)steps) * (8 * PI);
		float r = a + (b * cos(theta));

		Polar p{ time + theta, r };
		DrawCircle(p, 0.2f, WHITE);
	}

#elif defined ROSE
	//r = a * cos( k * theta ) | OR | r = a * sin( k * theta )
	int steps = 200;
	float time = (float)GetTime();
	float a = 6.0f;     
	float k = 4.0f;     

	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float)steps) * (2 * PI);  
		float r = a * cos(k * theta);                

		Polar p{ theta + time, r };
		DrawCircle(p, 0.2f, PINK);
	}
#elif defined USER
	//Fermat’s Spiral/Parabolic Spiral (Thanks ChatGPT)
	//r = a · sqrt(theta)
	int steps = 300;
	float time = (float)GetTime();
	float a = 1.0f;

	for (int i = 1; i < steps; i++)
	{
		float theta = (i / (float)steps) * (6 * PI);
		float r = a * sqrt(theta); 

		Polar p{ theta + time, r };
		DrawCircle(p, 0.2f, SKYBLUE);
	}
#endif // 

	m_camera->EndMode();
}

void PolarScene::DrawGUI()
{
}
