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

	inline static Vector2 anchor01 = { 24, 72 };

	//dynamic values
	inline static float mass{ 1 };
	inline static float size{ 0.09f };
	inline static float damping{ 0.1f };
	inline static float gravity_scale{ 1 };
	inline static float restitution{ 1 };
	 
	inline static int type = 2; //0 = static, 1 = kinematic, 2 = dynamic
	 
	inline static bool select_active = false;
};