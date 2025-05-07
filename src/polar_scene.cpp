#include "polar_scene.h"

#define ARCHIMEDIAN
//#define CARDIOID
//#define LIMACON
//#define ROSE
//#define USER

void PolarScene::Initialize()
{
}

void PolarScene::Update()
{
}

void PolarScene::Draw()
{
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
#elif CARDIOID
	//r = a( 1 + cos(theta) )

#elif LIMACON
	//r = a + ( b * cos(theta) )

#elif ROSE
	//r = a * cos( k * theta ) | OR | r = a * sin( k * theta )

#elif USER
	//code

#endif // 
}

void PolarScene::DrawGUI()
{
}
