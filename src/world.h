#pragma once
#include "raylib.h"
#include <vector>

struct Body;
class Scene;

class World
{
public:
	~World();

	void Initialize(Vector2 gravity = Vector2{ 0,-9.81 }, size_t poolsize = 30);

	Body* CreateBody(const Vector2& position, float size,const Color& color);
	void Step(float timeStep);
	void Draw(const Scene& scene);

	void DestroyAll();

private:
	Vector2 m_gravity{0,0};
	std::vector<Body*> m_bodies;
};