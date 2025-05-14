#pragma once
#include "scene.h"

struct Body;

class VectorScene : public Scene
{
public:
	VectorScene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background)
	{
		//		
	}


	// Inherited via Scene
	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Draw() override;
	void DrawGUI() override;

private:
	Vector2 anchor01 = { 24, 24 };

	bool WindowBox000Active = true;
	float Slider001Value = 0.0f;
};