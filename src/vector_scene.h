#pragma once
#include "scene.h"
#include "math_utils.h"

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
	Vector2 anchor01 = { 24, 72 };
    
    bool PhysicsWindowActive = true;

	//dynamic values
	float mass{1};
	float size{0.09f};
	float damping{0.1f};
	float gravity_scale{1};
	float restitution{ randomf(0.5f, 1.0f) };

	int type = 2; //0 = static, 1 = kinematic, 2 = dynamic

	bool select_active = false;
};