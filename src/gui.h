#pragma once
#include "world.h"
#include "raylib.h"

class GUI
{
public:
	static void Update();
	static void Draw();

	static struct Body* GetBodyIntersect(const Vector2& position, bodies_t& bodies, const SceneCamera& camera);

public:
	inline static bool mouseOverGUI = false;
	inline static bool PhysicsWindowActive = true;

	inline static  Vector2 anchor01 = { 72, 48 };
	inline static  Vector2 anchor02 = { 96, 88 };
	inline static  Vector2 anchor03 = { 96, 280 };
	inline static  Vector2 anchor04 = { 96, 376 };

	//dynamic values
	inline static float mass{ 1.0f };
	inline static float size{ 0.8f };
	inline static float damping{ 0.1f };
	inline static float gravity_scale{ 1.0f };
	inline static float restitution{ 1.0f };
	 
	inline static int type = 2; //0 = static, 1 = kinematic, 2 = dynamic

	inline static float springDampingValue = 0.5f;
	inline static float stiffnessValue = 15.0f;

	inline static float gravitationValue = 0.0f;
	inline static float gravityValue = 0.0f;

	inline static bool simulateActive = true;
	inline static bool select_active = false;
	inline static bool resetPressed = false;
};